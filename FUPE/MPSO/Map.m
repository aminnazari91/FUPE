function NewValues=Map(Value, Min, Max)


    NewValues = ( Value - Min) / ( Max - Min );
    if (NewValues == 0)
        NewValues = NewValues+eps;
    end
    if (NewValues == 1)
        NewValues = NewValues-eps;
    end
    
end