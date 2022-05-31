import sys,requests,json,pathlib,time,pickle,getpass,os,subprocess
username = ""
password = ""
try:
	with open('spoj-submitter.dat', 'rb') as handle:
	    b = pickle.load(handle)
	username = b['username']
	password = b['password']
	handle.close()
except:
	print('\nLooks like you haven\'t specified the username and password yet\n')
	u = ""
	while(1==1):
		u = input("Enter your spoj username: ")
		if(u==""):
			print("Try again..")
		else:
			break
	p = ""
	while(1==1):
		p = getpass.getpass("Enter your spoj password: ")
		if(p==""):
			print("Try again..")
		else:
			break
	a = {'username': u,'password':p}
	f = open('spoj-submitter.dat', 'w+')
	with open('spoj-submitter.dat', 'wb') as handle:
		pickle.dump(a, handle, protocol=pickle.HIGHEST_PROTOCOL)
	f.close()
	handle.close()
	username = u
	password = p

#Check for valid arguments
try:
	qid = sys.argv[2]
	file = sys.argv[1]
except:
	print("Failed to start web scrapping. Please give a valid set of arguments.")
	print("Format: python spoj-submitter.py <filename> <problemname>")
	print("Sample use: python spoj-submitter.py myfile.cpp PRIME1")
	exit(0)
#End check for arguments

#Code to check is the file exists
pfile = pathlib.Path(file)
if not pfile.is_file():
	print('\nNo such file \''+file+'\' found. Please check for the location')
	exit(0)
#End code for file exists

print("\nSpecified File: "+file)

ch = (input("Do you want to test the problem in SPOJ Toolkit (y/n): ")).lower()

if (ch not in ['n', 'no']):
	c = subprocess.Popen(["g++",file,"-o","Program"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	time.sleep(2)
	if(os.path.isfile('Program')==False):
		print('Compilation error');
		exit(0)
	header = {'Host':'www.spojtoolkit.com','User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:47.0) Gecko/20100101 Firefox/47.0','Accept':'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8','Accept-Language':'en-US,en;q=0.5','Accept-Encoding':'gzip, deflate','Referer':'https://www.spojtoolkit.com/'}
	url = 'https://www.spojtoolkit.com/history/'+qid+'/'
	try:
		r=requests.get(url,headers=header,allow_redirects=False)
	except:
		print("Connection error. Make sure you are connected to Internet")
		exit(0)
	test_string = r.content.decode(errors='ignore').split('<pre')
	test_cases = []
	for i in range(1,len(test_string)):
		case = test_string[i].split('</pre>')[0].split('>')[1]
		payload = {'problemId':qid, 'testInput': case, 'timeLimit': '1', 'type':'codeTest', 'cache':'1'}
		r = requests.post('https://spojtoolkit.com/src-drivers/ExecuteCodeOnAPI-driver.php',headers=header,allow_redirects=False,data=payload)
		r = json.loads(r.content.decode(errors='ignore'))
		if(r['status']!="AC"):
			print("There was some issue with the testcase/server? Do you wish to submit directly?")
			break
		else:
			correct_answer = r['msg']
			f = open('temp.txt','w')
			f.write(case)
			f.close()
			f = open('temp.txt', 'r')
			p = subprocess.Popen("./Program",stdout=subprocess.PIPE,stdin=f)
			output = p.communicate()[0].decode('ascii')
			if(output!=correct_answer):
				print("Wrong answer in case no. "+str(i)+"\n\n**Your output**\n\n"+output+"\n\n**Expected output**\n\n"+correct_answer)
				exit(0)
			else:
				print('Case no. '+str(i)+" passed")

#Common headers for all requests
header = {'Host':'www.spoj.com','User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:47.0) Gecko/20100101 Firefox/47.0','Accept':'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8','Accept-Language':'en-US,en;q=0.5','Accept-Encoding':'gzip, deflate','Referer':'https://www.spoj.com/'}
#End common headers

#Check if the problem exists
url = 'https://www.spoj.com/problems/'+qid+'/'
try:
	r=requests.get(url,headers=header,allow_redirects=False)
except:
	print("Connection error. Make sure you are connected to Internet")
	exit(0)
problem=""
try:
	problem = str(r.content).split('<div id="problem-body">')[1].split('</div>')[0]
except:
	print('\nNo such problem found on spoj. Try again')
	exit(0)

print("Specified problem: "+qid)
#End check for problem

#Send login data
login_data = {'next_raw':'','autologin':'1','login_user':username,'password':password}
try:
	r=requests.post('https://www.spoj.com/login/',data=login_data,headers=header,allow_redirects=False)
except:
	print("\nConnection error. Falied to login")
	exit(0)
header['Cookie'] = r.headers['Set-Cookie'].split('; ')[0]
#Login data sent and session ID captured

#Check if login successful
if(len(r.headers['Set-Cookie'].split('autologin_hash'))<2):
	print('\nLogin failed. The credentials in the file may be wrong/tampered. Please re-run the application to enter new credential')
	os.remove("spoj-submitter.dat")
	exit(0)
else:
	print('\nLogin successful')
#End code to check login

#Check the language code
lcodes={}
lang = -1
url = 'https://www.spoj.com/submit/'+qid+'/'
try:
	r=requests.get(url,headers=header,allow_redirects=False)
except:
	print("Connection error. Make sure you are connected to Internet")
r=str(r.content).split('<option value="')
for i in range(1,len(r)):
	r[i] = r[i].split('" >')
	lcodes[int(r[i][0])] = r[i][1].split('</option>')[0]
while(1==1):
	language = input("\nEnter the language (For example: java8,java,c++,gcc etc, 0 to list all): ")
	if(language=="0"):
		print()
		for key in lcodes:
			print(str(key)+ "\t:\t" +lcodes[key])
		print()
	else:
		lang = -1
		for key in lcodes:
			if((lcodes[key].lower()).find((language.lower()))!=-1):
				lang = key
				print('\nLanguage selected: '+lcodes[key]+" ("+str(key)+")\n")
				break
		if(lang!=-1):
			break
		else:
			print("\nInvalid code. Try again..")
			continue
#End language check

#All checks have passed now. Upload the file
file = {'subm_file': open(file,'rb')}
upload_data = {'lang': lang, 'problemcode': qid, 'file': '', 'submit':'Submit!'}
try:
	r = requests.post('https://www.spoj.com/submit/complete/', headers=header,files=file,data=upload_data)
except:
	print("\nConnection error. Problem couldn't be submitted")
	exit(0)
print("\nSolution submitted..")
#File upload complete

def clean(s):
	s = s.replace("\\n", "")
	s = s.replace("\\t", "")
	s = s.replace(" ","")
	s = s.strip()
	return s

#Check for the the result
print("\nRunning Judge..\n")
url = 'https://www.spoj.com/status/'+qid+','+username+'/'
while(1==1):
	try:
		r=str(requests.get(url,headers=header).content)
	except:
		print("Connection error. Failed to fetch status")
		exit(0)
	status=int(clean((r.split('" status="'))[1].split('"')[0]))
	if(status<10):
		time.sleep(3)
		continue
	s=""
	if(status==15):
		s="Accepted"
	elif(status==14):
		s="Wrong Answer"
	elif(status==13):
		s="Time Limit Exceeded"
	elif(status==12):
		s="Runtime Error"
	elif(status==11):
		s="Compilation Error"
	elif(status==10):
		s="Disqualified"
	else:
		s="Unknown status"
	t=clean((r.split('best solutions">'))[1].split('<')[0])
	m=clean((r.split('id="statusmem_'))[1].split('>')[1].split('<')[0])
	print("Status : "+s)
	print("Time : "+t)
	print("Memory : "+m)
	break
