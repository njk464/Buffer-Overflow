IP = 192.168.56.101
# modify the above variable to your own configuration

# sends all data to the virtual machine in .tgz file.
# Also sends this makefile
send:
	tar -cvzf proj2-tar.tgz proj2-files/
	sshpass -p 'user' scp proj2-tar.tgz user@$(IP):/home/user/
	sshpass -p 'user' scp makefile user@$(IP):/home/user/
	sshpass -p 'user' ssh user@$(IP) make create 
# compiles everything and called from send
create:
	tar zxvf proj2-tar.tgz 
	cd proj2-files/targets/ && make clean && make && make install
	cd proj2-files/sploits/ && make clean && make 
# used to connect to the virtual machine
connect:
	sshpass -p 'user' ssh user@$(IP)

# MUST HAVE sshpass INSTALLED!!!!
