
function model=CreateDevices(NIoT, NFD, NFG, NCSDN)
    % Create All Things
    % Step1 : Create IoT Device and their Jobs (Cloudlet)
    % Create a VM for each Cloudlet
    % Step2 : Create Fog Device (Hosts)
    % Step3 : Create Fog Gateway (Brokers)
    % Step4 : Create SDN Cloud (CIS)
    %% Number of IoT Types (Job Type) 
    NIoTType = 4;
    
    IoTT1.CPU = 500;    %mips (length)
    IoTT1.Ram = 256;    %MB
    IoTT1.BW = 500;     %bps
    
    IoTT2.CPU = 1000;
    IoTT2.Ram = 512;
    IoTT2.BW = 1000;
    
    IoTT3.CPU = 2000;
    IoTT3.Ram = 512;
    IoTT3.BW = 1000;
    
    IoTT4.CPU = 5000;
    IoTT4.Ram = 1024;
    IoTT4.BW = 1000;
    
    %% CPU and Ram Requirement IoT
    EmptyIoTD.Type=[];
    EmptyIoTD.TypeName='';
    IoTD=repmat(EmptyIoTD,1, NIoT);
    for i=1:NIoT
        if (i <= NIoT/NIoTType)
            IoTD(i).Type = IoTT1;
            IoTD(i).TypeName = 'Type1';
        elseif (i > NIoT/NIoTType && i <= 2*NIoT/NIoTType)
            IoTD(i).Type = IoTT2;
            IoTD(i).TypeName = 'Type2';
        elseif (i > 2*NIoT/NIoTType && i <= 3*NIoT/NIoTType)
            IoTD(i).Type = IoTT3;
            IoTD(i).TypeName = 'Type3';
        else
            IoTD(i).Type = IoTT4;
            IoTD(i).TypeName = 'Type4';
        end
    end
    
    %% Number of Fog Devices Types 
    NFDType=2;
    
    FDT1.CPU = 5000;        %mips
    FDT1.Ram = 8*1024;      %MB  
    FDT1.BW = 10000;        %bps
    FDT1.Cores = 2;
    
    FDT2.CPU = 10000;
    FDT2.Ram = 16*1024;
    FDT2.BW = 20000;
    FDT2.Cores = 4;
    
    %% CPU and Ram Requirement FD
    EmptyFD.Type=[];
    FD=repmat(EmptyFD,1, NFD);
    for i=1:NFD
        if (i <= NFD/NFDType)
            FD(i).Type = FDT1;
        else
            FD(i).Type = FDT2;
        end
    end
    
    %% Location of Fog Devices
    xmin=0;
    xmax=100; %100Km
    
    ymin=0;
    ymax=100; %100Km
    
    x=randi([xmin xmax],1,NIoT+NFD+NFG);
    y=randi([ymin ymax],1,NIoT+NFD+NFG);
    
    % Distance of Fog Devices
    d=zeros(NIoT+NFD+NFG,NIoT+NFD+NFG);
    for i=1:NIoT+NFD+NFG
        for i2=i+1:NIoT+NFD+NFG
            d(i,i2)=sqrt((x(i)-x(i2))^2+(y(i)-y(i2))^2);
            d(i2,i)=d(i,i2);
        end
    end
    
    dmax=max(max(d));
    level1=dmax/3;
    level2=2*dmax/3;
    
    %% Save to Model
    model.NIoT=NIoT;
    model.NFD=NFD;
    model.NFG=NFG;
    model.NCSDN=NCSDN;
    
    model.IoTType=IoTD;
    model.FDType=FD;
    
    IoTFeatures=[IoTD(1:end).Type];
    FDFeatures=[FD(1:end).Type];
    
    model.CPUR=[IoTFeatures.CPU];
    model.CPUC=[FDFeatures.CPU].*[FDFeatures.Cores];
    
    model.RamR=[IoTFeatures.Ram];
    model.RamC=[FDFeatures.Ram];
    
    model.BWR=[IoTFeatures.BW];
    model.BWC=[FDFeatures.BW];
   
    model.X=x;
    model.Y=y;
    model.D=d;
    model.Level1=level1;
    model.Level2=level2;

end