        Uses Math;
		var 
            i, x, temp: integer;
            result, value, offset: float;
        begin
            for i := 1 to 10 do
                if x > 0 then
                    result := (value * 25 + (offset / 100)) - 42;
            
            // Try to use an undeclared variable
            temp := 10;  // This should generate an error
            
            // Try to redeclare a variable
            i:=10;  // This should generate an error
        end.