function NetU = NetUtility (model, Position, Delay)
     
    NFD = model.NFD;
    CPU = model.CPUR;
    Net = zeros(1,NFD);
    CPUC = model.CPUC;
    for i=1:NFD
        Idx = Position==i;
        %RunTime = sum(CPU(Idx))/CPUC(i);
        RunTime = sum(CPU(Idx))/CPUC(i);
        Net(i) = sum(Delay(Idx).*CPU(Idx))/RunTime;
        if isnan(Net(i))
            Net(i) = 0;
        end
    end
    
    NetU = mean(Net);
end