function subTasks = SplitJobs(model)

    % taskUnit.CPU = 1
    % taskUnit.Ram = 2
    subTasks=zeros(1,model.NIoT);
    
    TypeName={model.IoTType.TypeName};
    for i=1:model.NIoT
        if (strcmp(TypeName{i} ,'Type1'))
            subTasks(i)=2;
        elseif (strcmp(TypeName{i} ,'Type2'))
            subTasks(i)=3;
        elseif (strcmp(TypeName{i} ,'Type3'))
            subTasks(i)=4;
        else
            subTasks(i)=5;         
        end
    end
end