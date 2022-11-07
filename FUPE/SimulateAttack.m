function [CreditIoTD, RateIoTD] = SimulateAttack(IOTDevice,  AttackRate, RequestRate, RequestRateFactorAttack)

    MaxTime = 1;
    RateIoTD = zeros(IOTDevice, MaxTime);
    CreditIoTD = zeros(IOTDevice, MaxTime);
    
    NumDestructiveIoTD = floor(AttackRate*IOTDevice);
    for i=1:IOTDevice
        if i<=NumDestructiveIoTD
            CreditIoTD(i,:) = RequestRate*(1-AttackRate)*60;
            RateIoTD(i,:) = RequestRate*60+RequestRate*AttackRate*60*RequestRateFactorAttack;
        else
            CreditIoTD(i,:) = RequestRate*60;
            RateIoTD(i,:) = RequestRate*60;
        end
    end
end