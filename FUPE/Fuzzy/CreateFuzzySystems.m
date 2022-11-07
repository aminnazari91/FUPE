clear, clc;
[Security, Utility] = CreateMemberFunction();

%Security = AddRulesSecurity(Security);
%Utility = AddRulesUtility(Utility);
%writefis(Security, 'FuzzySecurity');
%writefis(Utility, 'FuzzyUtility');