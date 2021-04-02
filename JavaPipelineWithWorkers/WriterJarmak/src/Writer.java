import ru.spbstu.pipeline.*;


import java.io.*;
import java.util.Arrays;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Writer implements IWriter {
    private final Logger log;
    private FileOutputStream fos;
    private final WriterGrammar writerGrammar;
    private static IProducer producer;
    private static IMediator mediator;
    private List<Lexem> lexems;
    private final TYPE[] types = new TYPE[3];
    private TYPE finalType = null;

    private byte[] buffer;
    private static int cBytes;
    private static int pos;

    public Writer(Logger log) {
        this.log = log;
        this.writerGrammar = new WriterGrammar(new String[]{Grammar.BYTE_COUNT.getStrConfig()});
        types[0] = TYPE.BYTE; types[1] = TYPE.CHAR; types[2] = TYPE.SHORT;
    }

    public RC setConfig(String cfg) {
        this.log.log(Level.INFO, "Read cfg for writer");
        lexems = WriterParser.getGrammar(cfg, writerGrammar, log);
        if (lexems == null)
            return RC.CODE_CONFIG_GRAMMAR_ERROR;
        RC msg = WriterParser.paramAnalysis(lexems, writerGrammar, log);
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

    public RC setOutputStream(FileOutputStream fos) {
        this.fos = fos;
        return RC.CODE_SUCCESS;
    }

    public RC setConsumer(IConsumer c) {
        log.log(Level.WARNING, "You cannot set consumer to writer!");
        return RC.CODE_FAILED_PIPELINE_CONSTRUCTION;
    }

    public RC setProducer(IProducer p) {
        producer = p;
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
                    else if (pTypes[i].equals(TYPE.SHORT) && finalType != null){
                        finalType = TYPE.SHORT;
                    }
                }
            }
        }
        if (finalType == null){
            log.log(Level.WARNING, "No overlap by datatype with writer and his producer");
            return RC.CODE_FAILED_PIPELINE_CONSTRUCTION;
        }

        mediator = p.getMediator(finalType);
        return RC.CODE_SUCCESS;
    }

    private RC writeData(byte[] data, int size){
        if (size == 0)
            return RC.CODE_SUCCESS;

        try{
            fos.write(data, 0, size);

        }catch (IOException e){
            log.log(Level.WARNING, "Something wrong with data writing process");
            return RC.CODE_FAILED_TO_WRITE;
        }

        return RC.CODE_SUCCESS;
    }

    /*
     *
     * Дописать считывание данных от продюсера с хранением их в некотором диапазоне
     *
     *
     * */

    public RC execute() {
        this.log.log(Level.INFO, "Writer try execute");
        byte[] array = null;

        switch (finalType){
            case SHORT:
                short[] dataS = (short[])mediator.getData();
                if (dataS == null)
                    break;

                array = new byte[dataS.length * 2];

                for (int i = 0, k = 0; i < dataS.length; i += 2, k++){
                    array[i]     = (byte)(dataS[k] & 0xff);
                    array[i + 1] = (byte)((dataS[k] >> 8) & 0xff);
                }
                break;

            case CHAR:
                char[] dataC = (char[])mediator.getData();
                if (dataC == null)
                    break;
                array = new String(dataC).getBytes();
                break;
            case BYTE:
                array = (byte[])mediator.getData();
        }

        if (array == null){ //Данных больше не будет

            return writeData(buffer, pos);
        }

        // Кладем данные в буффер - хранилище
        if (array.length < cBytes - pos){
            System.arraycopy(array, 0, buffer, pos, array.length);
            pos += array.length;
        }
        else{
            byte[] writeArray = new byte[array.length + pos];
            System.arraycopy(buffer, 0, writeArray, 0, pos);
            for (int i = 0, k = pos; i < array.length; i++, k++){
                writeArray[k] = array[i];
            }

            RC msg = writeData(writeArray, writeArray.length);
            if (msg != RC.CODE_SUCCESS)
                return msg;

            Arrays.fill(buffer, (byte)0);
            pos = 0;
        }

        return RC.CODE_SUCCESS;
    }

}
