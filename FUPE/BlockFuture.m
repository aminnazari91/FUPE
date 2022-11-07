function DestructiveIoTD = BlockFuture(IOTDevice, CreditIoTD, RateIoTD)

securityLevel = zeros(1,IOTDevice);
for i = 1:IOTDevice
    credit = sum(CreditIoTD(i,:));
    rate = sum(RateIoTD(i,:));
    % Normalaize credit, rate
    credit =  Map(credit, min(sum(CreditIoTD,2)), max(sum(CreditIoTD,2)));  
    rate =  Map(rate, min(sum(RateIoTD,2)), max(sum(RateIoTD,2)));
    %
    securityLevel(i) =  mainSecurity(credit, rate);
end

TP = 0.8;
DestructiveIoTD = [];
for i=1:floor(IOTDevice)
    if (securityLevel(i)<0.5)
        DestructiveIoTD = [DestructiveIoTD i];%#ok
    end
end
idx = randsample(length(DestructiveIoTD), floor(length(DestructiveIoTD)*TP));
DestructiveIoTD = DestructiveIoTD(idx);
end