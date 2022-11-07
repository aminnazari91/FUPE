function Position=Moving(Position, LBestPosition, GBestPosition, w1, w2)
    
    n = length(Position);
    % To GBest
    g = randsample(n, floor(n*w1));
    Position(g) = GBestPosition(g);
    
    % To LBest
    l = randsample(n, floor(n*w2));
    Position(l) = LBestPosition(l);
    
end