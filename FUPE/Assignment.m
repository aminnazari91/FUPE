function Position=Assignment(Model, Method, Rate, Safe)

    if strcmp(Method,'GAPSO')
        %addpath('GAPSO');
        %Position=GAPSO(Model, Credit, Rate);
        %Position = Position.Position;
    elseif strcmp(Method,'MPSO')
        addpath('MPSO');
        Position=MPSO(Model, Rate, Safe);
        Position = Position.Position;
    end

end