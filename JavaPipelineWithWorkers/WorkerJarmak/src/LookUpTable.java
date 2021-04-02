import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Arrays;
import java.util.Hashtable;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

import ru.spbstu.pipeline.*;

// Таблица подстановки
public class LookUpTable implements IExecutor {
    private final Logger log;
    private final TYPE[] types = new TYPE[1];
    private final LookUpTableGrammar lktgrammar;
    private Hashtable<Byte, Byte> lkt = new Hashtable();
    private byte[] replaced;
    private List<Lexem> lexems;

    private IProducer producer;
    private IConsumer consumer;
    private IMediator mediator;

    public LookUpTable(Logger log) {
        this.log = log;
        this.lktgrammar = new LookUpTableGrammar(new String[]{Grammar.TABLE.getStrConfig()});
        this.types[0] = TYPE.BYTE;
    }

    private boolean addTable(byte[] bytes) {
        if (bytes.length % 2 != 0) {
            return false;
        } else {
            for(int i = 0; i < bytes.length; i += 2) {
                if (this.lkt.containsKey(bytes[i])) {
                    return false;
                }

                if (this.lkt.containsValue(bytes[i + 1])) {
                    return false;
                }

                this.lkt.put(bytes[i], bytes[i + 1]);
            }

            return true;
        }
    }

    private byte[] workWithData(byte[] toReplace) {
        byte[] replacedR = new byte[toReplace.length];

        for(int i = 0; i < toReplace.length; ++i) {
            if (this.lkt.containsKey(toReplace[i])) {
                replacedR[i] = (Byte)this.lkt.get(toReplace[i]);
            } else {
                replacedR[i] = toReplace[i];
            }
        }

        return replacedR;
    }

    @Override
    public RC setConfig(String cfg) {
        this.log.log(Level.INFO, "Set LookUpTable config");
        lexems = ExecutorParser.getGrammar(cfg, lktgrammar, log);
        if (lexems == null)
            return RC.CODE_CONFIG_GRAMMAR_ERROR;
        RC msg = ExecutorParser.paramAnalysis(lexems, lktgrammar, log);
        if (msg != RC.CODE_SUCCESS)
            return msg;

        for (Lexem lex : lexems) {

            if (lex.getToken().equals(Grammar.TABLE.getStrConfig()) && lkt.isEmpty()) {
                try {
                    FileInputStream fis = new FileInputStream(lex.getData());
                    byte[] table = new byte[fis.available()];
                    fis.read(table, 0, fis.available());
                    fis.close();
                    if (!this.addTable(table)) {
                        this.log.log(Level.WARNING, "Broken bijection in lookuptable");
                        return RC.CODE_INVALID_ARGUMENT;
                    }
                } catch (FileNotFoundException e) {
                    log.log(Level.WARNING, "In worker " + e.getMessage());
                    return RC.CODE_CONFIG_SEMANTIC_ERROR;
                } catch (IndexOutOfBoundsException | NullPointerException e) {
                    log.log(Level.WARNING, "In worker " + e.getMessage());
                    return RC.CODE_CONFIG_SEMANTIC_ERROR;
                } catch (IOException e) {
                    log.log(Level.WARNING, "In worker " + e.getMessage());
                    return RC.CODE_CONFIG_SEMANTIC_ERROR;
                }
            }
        }

        return RC.CODE_SUCCESS;
    }

    @Override
    public RC setConsumer(IConsumer c) {
        this.consumer = c;
        return RC.CODE_SUCCESS;
    }

    @Override
    public RC setProducer(IProducer p) {
        this.producer = p;
        TYPE finalType = null;

        TYPE[] pTypes = p.getOutputTypes();

        for (int i = 0; i < pTypes.length; i++) {
            for (int j = 0; j < types.length; j++){

                if (types[j].equals(pTypes[i])){
                    if (pTypes[i].equals(TYPE.BYTE)){
                        finalType = TYPE.BYTE;
                    }
                    else if (pTypes[i].equals(TYPE.CHAR) && finalType != null){
                        finalType = TYPE.CHAR;
                    }
                    else if (pTypes[i].equals(TYPE.SHORT ) && finalType != null){
                        finalType = TYPE.SHORT;
                    }
                }
            }
        }
        if (!finalType.equals(TYPE.BYTE)){
            log.log(Level.WARNING, "No overlap by data type in the LKT worker");
            return RC.CODE_FAILED_PIPELINE_CONSTRUCTION;
        }

        mediator = p.getMediator(finalType);

        return RC.CODE_SUCCESS;
    }


    @Override
    public TYPE[] getOutputTypes() {

        return types;
    }

    @Override
    public IMediator getMediator(TYPE type) {
        // Здесь слздается посредник для консьюмеора
        return new LookUpTable.LktMediator(type);
    }

    @Override
    public RC execute() {
        this.log.log(Level.INFO, "LookUpTable try execute");

        byte[] toReplace = (byte[])mediator.getData();
        if (toReplace == null)
            replaced = null;
        else
            replaced = workWithData(toReplace);

        consumer.execute();

        return RC.CODE_SUCCESS;
    }

    class LktMediator implements IMediator{

        private final TYPE type;

        LktMediator(TYPE type){
            this.type = type;
        }

        @Override
        public Object getData() {
            if (replaced == null)
                return null;
            switch (type){
                case BYTE:
                    return replaced.clone();
                case CHAR:
                    String temp = Arrays.toString(replaced);
                    return temp.toCharArray();
                case SHORT:
                    short[] shortBuffer = new short[replaced.length / 2];
                    for (int i = 0, k = 0; i < replaced.length; i += 2, k++){
                        shortBuffer[k] = (short)((replaced[i + 1] << 8) + (replaced[i] & 0xff));
                    }
                    return shortBuffer;
            }

            return null;
        }
    }
}
