function [SuccessConnection, Rate] = CreateProfile(NFD, MaxTime, ...
    AttackRate, NumFogDeviceAttacked, RequestRate, RequestRateFactorAttack)

    SuccessConnection = zeros(NFD,MaxTime);
    Rate = zeros(NFD,MaxTime);
    
    for i=1:NFD
        if i<=NumFogDeviceAttacked
            SuccessConnection(i,:) = RequestRate*(1-AttackRate)*60;
            Rate(i,:) = RequestRate*60+RequestRate*AttackRate*60*RequestRateFactorAttack;
        else
            SuccessConnection(i,:) = RequestRate*60;
            Rate(i,:) = RequestRate*60;
        end
    end
        
end