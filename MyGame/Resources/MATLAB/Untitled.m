
res = zeros(146,101,191);
for atk = 5 : 150
    for def = 0 : 100
        for hp = 10 : 200
            if (atk - def < 5)
                damage = 5;
            else
                damage = atk - def;
            end
            
            res(atk-4,def+1,hp-9) = hp / damage;
        end
    end
end