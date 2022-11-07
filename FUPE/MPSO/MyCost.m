function z = MyCost(q, Model,Rate)

    z = DelayCost(q, Model, Rate)/UtilityCost(q, Model);
end



function z = DelayCost(Position, Model, Rate)
    
    TrafficDelay = 0.01;
    Delay = zeros(1, Model.NIoT);
    for i=1:Model.NFD
        jobs = find(Position == i);
        CPUC = Model.CPUC(i);
        RamC = Model.RamC(i);
        BWC = Model.BWC(i);
        
        for j=1:length(jobs)
            CPUR = Model.CPUR(jobs(j));
            RamR = Model.RamR(jobs(j));
            if (CPUR<CPUC && RamR<RamC) 
                % Delay = Link Delay + TrafficVolume * Traffic Delay
                Delay(jobs(j)) = CPUR/BWC + Rate(i, 1)*TrafficDelay;
            else
                CPUC = Model.CPUC(i);
                RamC = Model.RamC(i);
                Delay(jobs(j)) = max(Delay(jobs)) + CPUR/BWC + Rate(i, 1)*TrafficDelay;
            end
            CPUC = CPUC-CPUR;
            RamC = RamC-RamR;
        end
    end
    z = sum(Delay);
end


function z = UtilityCost(q, Model)    
    CPUC = Model.CPUC;
    CPUR = Model.CPUR;
    
    RamC = Model.RamC;
    RamR = Model.RamR;
    
    BWC = Model.BWC;
    BWR = Model.BWR;
    
    utility = zeros(1, Model.NFD);
    
    for i=1:Model.NFD
        vms = q == i;
        meanLen = mean(CPUR(vms));
        cpuc = Map(CPUC(i), min(CPUC), max(CPUC));
        ramc = Map(RamC(i), min(RamC), max(RamC));
        bwc = Map(BWC(i), min(BWC), max(BWC));
        utility(i) = mainUtility(cpuc, ramc, bwc, meanLen);
        
    end
    z = mean(utility);
    %{
    for i=1:length(q)
        cpuc = CPUC(q(i));
        ramc = RamC(q(i));
        bwc = BWC(q(i));
        
        len = CPUR(i);
        ramr = RamR(i);
        
        % Normalaize cpuc, ramc, len
        cpuc = Map(cpuc, min(CPUC), max(CPUC));
        ramc = Map(ramc, min(RamC), max(RamC));
        bwc = Map(bwc, min(BWC), max(BWC));
        len = Map(len, min(CPUR), max(CPUR)); 
        %
        
        utility(i) = mainUtility(cpuc, ramc, bwc, len);
        
        CPUC(q(i)) = CPUC(q(i))-len;
        RamC(q(i)) = RamC(q(i))-ramr;
        if  CPUC(q(i))<=0 || RamC(q(i))<=0 
        	CPUC = Model.CPUC;
        	RamC = Model.RamC;
        end
    end
    z = -(sum(utility));
    %}
end