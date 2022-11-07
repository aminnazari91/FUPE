clc, clear, close all;
warning off all;

addpath('FuzzySystem\Security\');
addpath('FuzzySystem\Utility\');

Method = 'MPSO';                            %

IOTDevice = [20 40 60 80 100];              %IOT Device
FogDevice = [ 5 10 15 20 25];               %Fog Device
FogGateway = 2;                             %Fog Gateway
CloudSDN = 1; 
AttackRate = [.1 .2 .3 .4 .5];              %Probability of Failure Connection

RequestRate = 10;                           %RequestRate per each Minute
RequestRateFactorAttack = 5;                %alpha

dirName = num2str(2);
mkdir(dirName)
    
%for iter = 1: 10

    iter = 1;
    dirName = num2str(iter);
    mkdir(dirName)
    
    f=2;
    NumFogDeviceAttacked = floor(FogDevice(f)/5);  %Number of FogDevice Attacked
    for i=1:length(IOTDevice)
        FileName = ([dirName '\FPSTS_' num2str(FogDevice(f)) 'FD_' num2str(IOTDevice(i)) 'IoTD_' num2str(AttackRate(3)*100) 'AR']);
        disp(FileName)
        [Model] = CreateModel(IOTDevice(i), FogDevice(f), FogGateway, CloudSDN, ...
            AttackRate(3), NumFogDeviceAttacked, RequestRate, RequestRateFactorAttack);

        [subTasks] = SplitJobs(Model);

        [Credit, Rate] = GetInfoCloudSDN(Model);
        
        [CreditIoTD, RateIoTD] = SimulateAttack(IOTDevice(i), AttackRate(3), RequestRate, RequestRateFactorAttack);
        SafeDevices = Security(Model, Credit, Rate);
        Position =  Assignment(Model, Method, Rate, SafeDevices);
        
        [ResponseTime, MaxResponseTime, LoadBalance, Delay, MaxDelay, NetU, Utility] =...
            Evaluation(Model, Rate, Position);
        
        DestructiveIoTD = BlockFuture(IOTDevice(i), CreditIoTD, RateIoTD);
        save(FileName, 'ResponseTime', 'MaxResponseTime', 'LoadBalance', 'Delay', ...
            'MaxDelay', 'NetU', 'Utility', 'Position'); 
    end

    f=2;
    NumFogDeviceAttacked = floor(FogDevice(f)/5);  %Numberof FogDevice Attacked
    for j=1:length(AttackRate)
        FileName = ([dirName '\FPSTS_' num2str(FogDevice(f)) 'FD_' num2str(IOTDevice(3)) 'IoTD_' num2str(AttackRate(j)*100) 'AR']);
        disp(FileName)
        [Model] = CreateModel(IOTDevice(3), FogDevice(f), FogGateway, CloudSDN, ...
            AttackRate(j), NumFogDeviceAttacked, RequestRate, RequestRateFactorAttack);

        [subTasks] = SplitJobs(Model);
        
        [Credit, Rate] = GetInfoCloudSDN(Model);

        [CreditIoTD, RateIoTD] = SimulateAttack(IOTDevice(3), AttackRate(j), RequestRate, RequestRateFactorAttack);
        SafeDevices = Security(Model, Credit, Rate);
        Position =  Assignment(Model, Method, Rate, SafeDevices);
        
        [ResponseTime, MaxResponseTime, LoadBalance, Delay, MaxDelay, NetU, Utility] = Evaluation(Model, Rate, Position); %#ok
            
        
        DestructiveIoTD = BlockFuture(IOTDevice(3), CreditIoTD, RateIoTD); 
        save(FileName, 'ResponseTime', 'MaxResponseTime', 'LoadBalance', 'Delay', ...
            'MaxDelay', 'NetU', 'Utility', 'Position'); 
    end

    for f=1:length(FogDevice)
        NumFogDeviceAttacked = floor(FogDevice(f)/5);  %Numberof FogDevice Attacked
        FileName = ([dirName '\FPSTS_' num2str(FogDevice(f)) 'FD_' num2str(IOTDevice(3)) 'IoTD_' num2str(AttackRate(3)*100) 'AR']);
        disp(FileName)
        [Model] = CreateModel(IOTDevice(3), FogDevice(f), FogGateway, CloudSDN, ...
            AttackRate(3), NumFogDeviceAttacked, RequestRate, RequestRateFactorAttack);

        [subTasks] = SplitJobs(Model);

        [Credit, Rate] = GetInfoCloudSDN(Model);

        [CreditIoTD, RateIoTD] = SimulateAttack(IOTDevice(3), AttackRate(3), RequestRate, RequestRateFactorAttack);
        SafeDevices = Security(Model, Credit, Rate);
        Position =  Assignment(Model, Method, Rate, SafeDevices);
        
        [ResponseTime, MaxResponseTime, LoadBalance, Delay, MaxDelay, NetU, Utility] =...
            Evaluation(Model, Rate, Position);  
        
        DestructiveIoTD = BlockFuture(IOTDevice(3), CreditIoTD, RateIoTD);
        save(FileName, 'ResponseTime', 'MaxResponseTime', 'LoadBalance', 'Delay', ...
            'MaxDelay', 'NetU', 'Utility', 'Position'); 
    end

%end



