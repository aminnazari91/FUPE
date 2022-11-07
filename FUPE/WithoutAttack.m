Method = 'MPSO';                            %
f=2;
i=3;
FileName = ([dirName '\FPSTS_' num2str(FogDevice(f)) 'FD_' num2str(IOTDevice(i)) 'IoTD_' num2str(0) 'AR']);
disp(FileName)
[Model] = CreateModel(IOTDevice(i), FogDevice(f), FogGateway, CloudSDN, ...
    0, NumFogDeviceAttacked, RequestRate, RequestRateFactorAttack);

[subTasks] = SplitJobs(Model);

[Credit, Rate] = GetInfoCloudSDN(Model);

%[CreditIoTD, RateIoTD] = SimulateAttack(IOTDevice(i), 0, RequestRate, RequestRateFactorAttack);
SafeDevices = 1:1:Model.NFD;
Position =  Assignment(Model, Method, Rate, SafeDevices);

[ResponseTime, MaxResponseTime, LoadBalance, Delay, MaxDelay, NetU, Utility] =...
    Evaluation(Model, Rate, Position);

DestructiveIoTD = BlockFuture(IOTDevice(i), CreditIoTD, RateIoTD);
save(FileName, 'ResponseTime', 'MaxResponseTime', 'LoadBalance', 'Delay', ...
    'MaxDelay', 'NetU', 'Utility', 'Position'); 