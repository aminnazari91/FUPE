function [y1, y2]=Crossover(x1,x2)

    pSinglePoint=0.4;
    pDoublePoint=0.6;
    
    METHOD=RouletteWheelSelection([pSinglePoint pDoublePoint]);
    
    switch METHOD
        case 1
            [y1, y2]=SinglePointCrossover(x1,x2);
            
        case 2
            [y1, y2]=DoublePointCrossover(x1,x2);
            
    end

end