import java.io.*;
import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;
import ru.spbstu.pipeline.IExecutor;
import ru.spbstu.pipeline.IReader;
import ru.spbstu.pipeline.IWriter;
import ru.spbstu.pipeline.RC;


public class Manager {
    private final static Logger log = Logger.getLogger(Manager.class.getName());
    // ******************************************************************
    public static final MyGrammar myGrammar = new MyGrammar(); // Класс с набором токенов для грамматики
    private IReader reader; // reader and writer
    private IWriter writer;
    private final ArrayList<IExecutor> executors = new ArrayList<>(); // Список работников
    private FileOutputStream fos; // входной и выходной поток
    private FileInputStream fis;


    private static RC Message = RC.CODE_SUCCESS;
    // ********************************************************************

    public Manager(String cfg){
        log.log(Level.INFO, "Put config file to Manager");
        Map<String, String> configData = ManagerParser.getGrammar(cfg, myGrammar, log); // Данные для конфигурации
        if (configData == null)
            return;
        Message = ManagerParser.paramAnalysis(configData, myGrammar, log); // Семантический анализ данных из конфига.
        if (Message != RC.CODE_SUCCESS)
            return;
        ArrayList<Integer> positions = new ArrayList<>(); // Позиции работников

        Message = doConfigs(configData, positions); // Конфигурируем сессию
        if (Message != RC.CODE_SUCCESS)
            return;
        Message = makePipeline(positions); // Проектируем конвейер
    }

    // Run pipeline method
    public RC run(){
        log.log(Level.INFO, "Run application");
        if (Message != RC.CODE_SUCCESS)
            return Message;

        if (reader.execute() == RC.CODE_SUCCESS) {
            RC msg =  closeStreams();
            if (msg != RC.CODE_SUCCESS)
                return msg;
        }
        else
            return RC.CODE_FAILED_TO_READ;

        return RC.CODE_SUCCESS;
    }

    // Close stream method
    private RC closeStreams(){
        log.log(Level.INFO, "Close streams");
        try {
            fis.close();
            fos.close();
        } catch (IOException e){
            log.log(Level.WARNING, "Cannot close streams");
            return RC.CODE_INVALID_OUTPUT_STREAM;
        }

        return RC.CODE_SUCCESS;
    }
    // Вспомогательный класс для реализации интроспекции
    private Object makeClasses(String cls){

        try {
            Class clazz = Class.forName(cls);
            Class[] params = {Logger.class};
            return clazz.getConstructor(params).newInstance(log);
        } catch (ClassNotFoundException | InstantiationException | IllegalAccessException
                | NoSuchMethodException | InvocationTargetException e) {
            log.log(Level.WARNING, "Something wrong in executors creating process" + e.getMessage());
            Message = RC.CODE_FAILED_PIPELINE_CONSTRUCTION;
        }
        return null;
    }
    /*
     * Настройка сессии. Принимаем пакет с данными для конфигурации, а также массив, где будет храниться информация
     * о порядке следования работников на конвейере.
     * */
    private RC doConfigs(Map<String, String> configData, ArrayList<Integer> positions) {

        log.log(Level.INFO, "make manager session configuration");
        String data = null;

        data = configData.get(myGrammar.token(Grammar.READER_AND_CFG.ordinal()));
        if (data != null) {
            String[] reader_cfg = data.split(myGrammar.delimiterGr());
            if (reader_cfg.length != 2){
                log.log(Level.WARNING, "ERROR with reader and it`s cfg");
                return RC.CODE_FAILED_PIPELINE_CONSTRUCTION;
            }

            reader = (IReader)makeClasses(reader_cfg[0]);
            if (Message != RC.CODE_SUCCESS)
                return Message;
            Message = reader.setConfig(reader_cfg[1]);
            if (Message != RC.CODE_SUCCESS)
                return Message;
        }

        data = configData.get(myGrammar.token(Grammar.WRITER_AND_CFG.ordinal()));
        if (data != null) {
            String[] writer_cfg = data.split(myGrammar.delimiterGr());
            if (writer_cfg.length != 2){
                log.log(Level.WARNING, "ERROR with writer and it`s cfg");
                return RC.CODE_FAILED_PIPELINE_CONSTRUCTION;
            }

            writer = (IWriter)makeClasses(writer_cfg[0]);
            if (Message != RC.CODE_SUCCESS)
                return Message;
            Message = writer.setConfig(writer_cfg[1]);
            if (Message != RC.CODE_SUCCESS)
                return Message;
        }

        data = configData.get(myGrammar.token(Grammar.INPUT.ordinal()));

        if (data != null) {
            if (!new File(data).exists()) {
                log.log(Level.WARNING, "File input stream does not exist");
                return RC.CODE_INVALID_INPUT_STREAM;
            }

            try {
                fis = new FileInputStream(data);
            } catch (IOException e) {
                log.log(Level.WARNING, "Cannon open input stream");
            }
            reader.setInputStream(fis);
        }

        data = configData.get(myGrammar.token(Grammar.OUTPUT.ordinal()));
        if (data != null) {
            if (!new File(data).exists()) {
                log.log(Level.WARNING, "File output stream does not exist");
                return RC.CODE_INVALID_INPUT_STREAM;
            }

            try {
                fos = new FileOutputStream(data);
            } catch (IOException e) {
                log.log(Level.WARNING, "Something wrong in output stream" + e.getMessage());
            }
            writer.setOutputStream(fos);
        }

        data = configData.get(myGrammar.token(Grammar.EXECUTOR_NAME_AND_CFG.ordinal()));
        if (data != null) {
            log.log(Level.INFO, "Trying to create classes with java reflection methods");

            String[] class_config = data.split(myGrammar.delimiterGr());
            if (class_config.length % 2 != 0) {
                log.log(Level.WARNING, "ERROR in executor reading");
                return RC.CODE_INVALID_INPUT_STREAM;
            }

            // Creating methods with java reflection
            for (int i = 0; i < class_config.length; i += 2) {

                IExecutor executor = (IExecutor)makeClasses(class_config[i]);
                if (Message != RC.CODE_SUCCESS)
                    return Message;
                Message = executor.setConfig(class_config[i + 1]);
                if (Message != RC.CODE_SUCCESS)
                    return Message;
                executors.add(executor);
            }
        }
        data = configData.get(myGrammar.token(Grammar.ARRAY_OF_EXECUTOR_POS.ordinal()));
        if (data != null) {
            for (String str : data.split(myGrammar.delimiterGr())) {
                try {
                    Integer integer = Integer.parseInt(str);
                    if (integer < 0)
                        throw new NumberFormatException("Negative ceil numbers");
                    // Если такой номер имеется или он равен номеру для ридера, который всегда должен быть первым
                    if (positions.contains(integer - 1) || integer.equals(0)) {
                        log.log(Level.WARNING, "Array of executors pos error one. Reader first only");
                        return RC.CODE_INVALID_ARGUMENT;
                    }
                    positions.add(integer - 1);
                } catch (NumberFormatException e) {
                    log.log(Level.WARNING, "in ARRAY OF EXECUTORS POS or negative number" + e.getMessage());
                }
            }
        }
        if (data == null) {
            log.log(Level.WARNING, "ERROR in manager configuration null exception");
            return RC.CODE_CONFIG_GRAMMAR_ERROR;
        }


        return RC.CODE_SUCCESS;
    }

    // Формируем конвейер
    private RC makePipeline(ArrayList<Integer> positions){
        if (positions.size() != executors.size() || executors.size() == 0 || positions.size() == 0) {
            log.log(Level.WARNING, "Executors array is empty or array of pos not equal to executor array");
            return RC.CODE_FAILED_PIPELINE_CONSTRUCTION;
        }

        // Ставим работников на конвейер в соответствии с их порядковым номером
        reader.setConsumer(executors.get(positions.get(0)));
        Message = executors.get(positions.get(0)).setProducer(reader);
        if (Message != RC.CODE_SUCCESS)
            return Message;

        for (int j = 1; j < executors.size(); j++){
            executors.get(positions.get(j-1)).setConsumer(executors.get(positions.get(j)));
            Message = executors.get(positions.get(j)).setProducer(executors.get(positions.get(j-1)));
            if (Message != RC.CODE_SUCCESS)
                return Message;
        }

        Message = writer.setProducer(executors.get(positions.get(positions.size() - 1)));
        executors.get((positions.get(positions.size() - 1))).setConsumer(writer);

        return Message;
    }
}
