
function q = CreateRandomSolution(model, safeDevices)

    VM = model.NIoT;
    q = randi([min(safeDevices) max(safeDevices)],1,VM);

end