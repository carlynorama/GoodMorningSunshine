#!/usr/bin/python
# goodmorning_get.py
import os,sys
# add your curl url here, can be ftp, http (if server supports PUT), etc.
# ftp format:   'ftp://username:password@hostname/dirpath'
ftp_base_url = 'ftp://jooktest:Mk9MZu6G@test.jook.com/goodmorning'

if len(sys.argv) != 2 :
    print 'usage: goodmorning_get.py <filename>'
    sys.exit(1)

file_new = sys.argv[1]
file_old = file_new + '.old'
ftp_url  = ftp_base_url + '/' + file_new
ftp_get_cmd = 'curl --silent -R -O ' + ftp_url

# fetch the file from the remote server
rc = os.system( ftp_get_cmd )
if rc :
    print 'bad ftp rc:'+ str(rc)
    sys.exit(rc)

    file_old_time = 0
file_new_time = 0

if not os.path.isfile( file_old ):
    file_old_time = os.path.getmtime( file_old )
    
if os.path.isfile( file_new ):
    file_new_time = os.path.getmtime( file_new )
    time_diff = file_new_time - file_old_time
    print 'time diff mins: '+ str(int(time_diff/60))
    os.rename( file_new, file_old )
else:
    print 'bad files'

