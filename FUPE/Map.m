function NewValues=Map(Value, Min, Max)

    NewValues = ( Value - Min) / ( Max - Min );
    if (NewValues == 0)
        NewValues = NewValues+0.05;
    end
    if (NewValues == 1)
        NewValues = NewValues-0.05;
    end
    
end