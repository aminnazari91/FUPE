
function [z]=MyCost1(q, model)

    global initSol
    
    VM=model.VM;
    H=model.H;
    
    rcpu=model.rcpu;
    ccpu=model.ccpu;
    
    cram=model.cram;
    rram=model.rram;
    
    cbw=model.cbw;
    rbw=model.rbw;
    
    d=model.d;

    Pbusy=100;      %average energy consumption when the physical machine is fully utilized
    Pidle=10 ;      %average energy consumption when the physical machine is idle 
    w1=1;           %Weight Energy Consumption 
    w2=1;           %Weight Energy Migration
    
    e2=1;
    e3=3;
    e4=5;
    %% Energy
    UtilityCPU=zeros(1,H);
    EnergyConsumption=zeros(1,H);
    
    for i=1:H 
        wcpu=sum(rcpu(q==i));  
        UtilityCPU(i)=wcpu/ccpu(i);
        if (UtilityCPU(i)>0)
            EnergyConsumption(i)=Pidle+(Pbusy-Pidle)*UtilityCPU(i);
        end
    end
    
    %% Migration
    NumMigration=length(find(initSol~=q));
    
    EnergyMigration=zeros(1,NumMigration);
    
    Migration=find(initSol~=q);
    for i=1:NumMigration
        
        source=initSol(Migration(i));
        destination=q(Migration(i));
        distance=d(source,destination);
        if (distance<model.level1)
            EnergyMigration(i)=e2*rram(Migration(i));
        elseif(model.level1>distance && distance<model.level2)
            EnergyMigration(i)=e3*rram(Migration(i)); 
        else 
             EnergyMigration(i)=e4*rram(Migration(i));
        end
        
    end
    %% Utility
    UtilityCPU=zeros(1,H);
    UtilityMEM=zeros(1,H);
    UtilityBW=zeros(1,H);
    for i=1:H 
        wcpu=sum(rcpu(q==i));  
        UtilityCPU(i)=wcpu/ccpu(i);
        
        wram=sum(rram(q==i));  
        UtilityMEM(i)=wram/cram(i);
        
        wbw=sum(rbw(q==i));  
        UtilityBW(i)=wbw/cbw(i);
    end
    
    meUtilityCPU=mean(UtilityCPU);
    meUtilityMEM=mean(UtilityMEM);
    meUtilityBW=mean(UtilityBW);
    Utility=(meUtilityCPU+meUtilityMEM+meUtilityBW)/3;
    
    %% Load Balanc
    L=sqrt(sum((UtilityCPU-meUtilityCPU).^2)+ ... 
        sum((UtilityMEM-meUtilityMEM).^2)+sum((UtilityBW-meUtilityBW).^2));
    flag=infeasible(q,model);
    
    if ~flag
         
        
        z=w1*sum(EnergyConsumption)+w2*sum(EnergyMigration)+(1-Utility)+L;
        
    else
        
        z=inf;
        
    end
    
end