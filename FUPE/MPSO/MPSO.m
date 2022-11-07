function GBest=MPSO(model, Rate, safeDevices)

% Cost Function
CostFunction=@(q) MyCost(q, model, Rate);      

%% MPSO Parameters

MaxIt=100;               % Maximum Number of Iterations
nPop=100;                % Population Size

w1 = 0.5;
w2 = 0.2;
%% Initialization

% Create Empty Structure
empty_individual.Position=[];
empty_individual.Cost=[];
empty_individual.LBestPosition = [];
empty_individual.LBestCost = [];

% Create Structre Array to Save Population Data
pop=repmat(empty_individual,nPop,1);

% Initilize Population
for i=1:nPop
    % Create Random Solution (Position)
    Position=CreateRandomSolution(model, safeDevices);
    [Cost]=CostFunction(Position);
    
    pop(i).Position = Position;
    pop(i).Cost = Cost;
    pop(i).LBestPosition = Position;
    pop(i).LBestCost = Cost;
    
end

% Sort Population
Costs=[pop.Cost];
[~, SortOrder]=sort(Costs);
pop=pop(SortOrder);

% Store Best Solution Ever Found
GBest.Cost=pop(1).Cost; 
GBest.Position=pop(1).Position; 


%% Main Loop

for it=1:MaxIt
    it
    % Moving
    for i=1:nPop

        pop(i).Position=Moving(pop(i).Position, pop(i).LBestPosition, GBest.Position, w1, w2);
        pop(i).Cost=CostFunction(pop(i).Position);
              
        if (pop(i).Cost<pop(i).LBestCost)
            pop(i).LBestPosition = pop(i).Position;
            pop(i).LBestCost = pop(i).Cost;
        end
        
        % Sort Population
        Costs=[pop.Cost];
        [~, SortOrder]=sort(Costs);
        pop=pop(SortOrder);

        % Truncate Extra Individuals
        pop=pop(1:nPop);
        
        if (pop(1).Cost < GBest.Cost)
            GBest.Cost=pop(1).Cost; 
            GBest.Position=pop(1).Position; 
        end
    end


end

end