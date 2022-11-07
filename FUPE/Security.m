function SafeDevice = Security(Model, Credit, Rate)

    Credit = mean(Credit,2);
    Rate = mean(Rate,2);
    securityLevel = zeros(1, Model.NFD);
    SafeDevice = [];
    for i=1:Model.NFD
        credit =  Map(Credit(i), min(Credit), max(Credit));
        rate =  Map(Rate(i), min(sum(Rate,2)), max(sum(Rate,2)));
        securityLevel(i) = mainSecurity(credit, rate);
        if (securityLevel(i)>0.5)
            SafeDevice = [SafeDevice, i];%#ok
        end
    end
    

end