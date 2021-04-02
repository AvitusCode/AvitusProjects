import java.io.FileInputStream;
import java.io.IOException;
import java.util.Arrays;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

import ru.spbstu.pipeline.*;


public class Reader implements IReader {
    private final Logger log;
    private FileInputStream fis;
    private final ReaderGrammar readerGrammar;
    private final TYPE[] types = new TYPE[3];
    private byte[] buffer;

    private IConsumer executor;
    private List<Lexem> lexems;
    private static int cBytes;

    public Reader(Logger log) {
        this.log = log;
        this.readerGrammar = new ReaderGrammar(new String[]{Grammar.BYTE_COUNT.getStrConfig()});
        types[0] = TYPE.BYTE; types[1] = TYPE.CHAR; types[2] = TYPE.SHORT;
    }

    public RC setConfig(String cfg) {
        this.log.log(Level.INFO, "set config to Reader");
        lexems = ReaderParser.getGrammar(cfg, this.readerGrammar, this.log);
        if (lexems == null)
            return RC.CODE_CONFIG_GRAMMAR_ERROR;
        RC msg = ReaderParser.paramAnalysis(lexems, this.readerGrammar, this.log);
        if (msg != RC.CODE_SUCCESS)
            return msg;

        for (Lexem lex : lexems){
            if (lex.getToken().equals(Grammar.BYTE_COUNT.getStrConfig())){
                if (cBytes != 0)
                    return RC.CODE_CONFIG_GRAMMAR_ERROR;
                cBytes = Integer.parseInt(lex.getData());
                buffer = new byte[cBytes];
            }
        }

        return RC.CODE_SUCCESS;
    }

    public RC setInputStream(FileInputStream fis) {
        this.fis = fis;
        return RC.CODE_SUCCESS;
    }

    public RC setConsumer(IConsumer c) {


        this.executor = c;
        return RC.CODE_SUCCESS;
    }

    public RC setProducer(IProducer p) {
        return RC.CODE_INVALID_OUTPUT_STREAM;
    }

    @Override
    public TYPE[] getOutputTypes() {
        return types;
    }

    @Override
    public IMediator getMediator(TYPE type) {
        return new Reader.ReaderMediator(type);
    }

    public RC execute() {
        this.log.log(Level.INFO, "Reader try execute");
        int pos_end = 0;
        buffer = new byte[cBytes];

        try {
            int end = this.fis.available();
            if (end < cBytes || end % cBytes != 0){
                log.log(Level.WARNING, "ERROR: incorrect input file size!");
                return RC.CODE_FAILED_TO_READ;
            }

            while(pos_end < end) {
                this.fis.read(buffer, 0, cBytes);
                pos_end += cBytes;
                RC msg = this.executor.execute();
                if (msg != RC.CODE_SUCCESS) {
                    return msg;
                }
            }
            buffer = null;
            RC msg = this.executor.execute();
            if (msg != RC.CODE_SUCCESS) {
                return msg;
            }

        } catch (IndexOutOfBoundsException var5) {
            this.log.log(Level.WARNING, "Envalid index pos in reader");
            return RC.CODE_INVALID_ARGUMENT;
        } catch (NullPointerException var6) {
            this.log.log(Level.WARNING, "NullPointer exception in reader");
            return RC.CODE_INVALID_ARGUMENT;
        } catch (IOException var7) {
            this.log.log(Level.WARNING, var7.getMessage());
            return RC.CODE_INVALID_ARGUMENT;
        }

        return RC.CODE_SUCCESS;
    }

    class ReaderMediator implements IMediator{
        private final TYPE type;

        ReaderMediator(TYPE type){
            this.type = type;
        }

        @Override
        public Object getData() {
            if (buffer == null)
                return null;
            switch (type){
                case BYTE:
                    return buffer.clone();
                case CHAR:
                    String temp = Arrays.toString(buffer);
                    return temp.toCharArray();
                case SHORT:
                    short[] shortBuffer = new short[buffer.length / 2];
                    for (int i = 0, k = 0; i < buffer.length; i += 2, k++){
                        shortBuffer[k] = (short)((buffer[i + 1] << 8) + (buffer[i] & 0xff));
                    }
                    return shortBuffer;
            }

            return null;
        }
    }
}
