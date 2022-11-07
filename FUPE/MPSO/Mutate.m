function y=Mutate(x)
        
    r1=randi(length(x));
    r2=randi(length(x));
    
    temp=x(r1);
    x(r1)=x(r2);
    x(r2)=temp;
    
    y=x;
    
end