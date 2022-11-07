function [Model] = CreateModel(IOTDevice, FogDevice, FogGateway,...
    CloudSDN, AttackRate, NumFogDeviceAttacked, RequestRate,...
    RequestRateFactorAttack)

    %IOTDevice = [40 50 60 70 80 90 100];        %IOT Device
    %FogDevice = [10 10 15 15 20 20 20 ];        %Fog Device
    %FogGateway = 3;                             %Fog Gateway
    %CloudSDN = 1;                               %Cloud SDN
    %nModel=numel(IOTDevice);
    MaxTime = 24;
    
    Model = CreateDevices(IOTDevice, FogDevice, FogGateway, CloudSDN);
    
    [SuccessConnection, RequestRate] = CreateProfile(FogDevice, MaxTime,...
        AttackRate, NumFogDeviceAttacked, RequestRate,...
        RequestRateFactorAttack);
    
    Model.SuccessConnection = SuccessConnection;
    Model.RequestRate = RequestRate;

end