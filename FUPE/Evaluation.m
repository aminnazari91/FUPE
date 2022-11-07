function [ResponseTime, MaxResponseTime, Loadbalence, Delay, MaxDelay, NetU, Utility] =...
    Evaluation(Model, Rate, Position)

    TrafficDelay = 0.01;
    ResponseTime = zeros(1, Model.NIoT);
    Delay = zeros(1, Model.NIoT);
    Loadbalence = zeros(1, Model.NFD);
    Utility = zeros(1, Model.NFD);
    for i=1:Model.NFD
        jobs = find(Position == i);
        Loadbalence(i) = sum(Model.CPUR(jobs));
        Utility(i) = min(sum(Model.CPUR(jobs))/sum(Model.CPUC(i)), 1);
        CPUC = Model.CPUC(i);
        RamC = Model.RamC(i);
        BWC = Model.BWC(i);
        
        for j=1:length(jobs)
            CPUR = Model.CPUR(jobs(j));
            RamR = Model.RamR(jobs(j));
            if (CPUR<CPUC && RamR<RamC) 
                % ResponseTime = Link Delay + TrafficVolume * Traffic Delay + Run Time
                ResponseTime(jobs(j)) = CPUR/BWC + Rate(i, 1)*TrafficDelay + CPUR/CPUC;
                % Delay = Link Delay + TrafficVolume * Traffic Delay
                Delay(jobs(j)) = CPUR/BWC + Rate(i, 1)*TrafficDelay;
            else
                CPUC = Model.CPUC(i);
                RamC = Model.RamC(i);
                ResponseTime(jobs(j)) = max(ResponseTime(jobs)) + CPUR/BWC + ...
                    Rate(i, 1)*TrafficDelay + CPUR/CPUC;
                Delay(jobs(j)) = max(Delay(jobs)) + CPUR/BWC + Rate(i, 1)*TrafficDelay;
            end
            CPUC = CPUC-CPUR;
            RamC = RamC-RamR;
        end
        
    end
    MaxResponseTime = max(ResponseTime);
    MaxDelay = max(Delay);
    Utility (Utility==0) = [];
    NetU = NetUtility(Model, Position, Delay);
end
