netsh advfirewall firewall add rule name="RuleName" dir=in action=allow protocol=TCP localport=4343
netsh advfirewall firewall add rule name="RuleName" dir=out action=allow protocol=TCP localport=4343
netsh advfirewall firewall dump