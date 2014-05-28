#!/usr/bin/python
# goodmorning.py
import os,sys
# add your curl url here, can be ftp, http (if server supports PUT), etc.
# ftp format:   'ftp://username:password@hostname/dirpath'
base_url = 'ftp://jooktest:Mk9MZu6G@test.jook.com/goodmorning'
base_dir = "/tmp/";

if len(sys.argv) != 3 :
    print 'usage: goodmorning.py <get|set> <filename>'
    sys.exit(1)
cmd      = sys.argv[1]
fname    = sys.argv[2]
file_new = base_dir + fname
file_old = base_dir + fname + '.old'
full_url = base_url + '/' + fname
curl_get_cmd = 'curl --silent -R -o '+ file_new +' '+ full_url
curl_set_cmd = 'curl --silent --ftp-create-dirs --upload-file '+file_new+' '+full_url

def goodmorning_set():
    # send file to remote server (file contents unimportant, timestamp is)
    rc = os.system( 'echo "hello!" > '+file_new )
    rc = os.system( curl_set_cmd )
    
def goodmorning_get():
    # fetch the file from the remote server
    rc = os.system( curl_get_cmd )
    if rc :
        print '-' + str(rc)  # return bad news as neg number
        sys.exit(rc)
    file_old_time = 0
    file_new_time = 0

    if os.path.isfile( file_old ):
        file_old_time = os.path.getmtime( file_old )
    
    # compute timestamp differences
    if os.path.isfile( file_new ):
        file_new_time = os.path.getmtime( file_new )
        time_diff = file_new_time - file_old_time
        diffsecs = min(65000, int(time_diff))
        #print 'time diff mins: '+ str(diffmins)
        print str(diffsecs)
        os.rename( file_new, file_old )
    else:
        print "-1000"  # 'bad files'
        sys.exit(1)

if cmd == 'set' :
    #print "setting "+file_new
    goodmorning_set()

elif cmd == 'get' :
    #print "getting "+file_new
    goodmorning_get()
else :
    print "unrecognized cmd"
    sys.exit(1)

