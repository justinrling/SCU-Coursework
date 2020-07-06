
# Behnam Dezfouli
# CSEN, Santa Clara University

# This program implements a simple web server that serves html and jpg files

# Input arguments:
# argv[1]: Sever's port number


from socket import *  # Import socket module
import sys            # To terminate the program


if __name__ == "__main__":

    # check if port number is provided
	if len(sys.argv) != 2:
		print 'Usage: python %s <PortNumber>' % (sys.argv[0])
        	sys.exit()

    # STUDENT WORK
	#AF_INET is used for IPv4 protocols
	#(SOCK_STREAM is used for TCP)
	serverSocket = socket(AF_INET, SOCK_STREAM)	
	serverSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)	#to avoid the "address already in use" error
	serverPort = int(sys.argv[1])							#assign a port number
	serverSocket.bind(("", serverPort))						#s.bind((HOST, PORT))
	serverSocket.listen(1)									#listen to at most one connection at a time


    #Server should be up and running and listening to the incoming connections
	while True:
		print('The server is ready to respond to incoming requests...')
		connectionSocket, addr = serverSocket.accept()	#set up a new connection from the client
		message = connectionSocket.recv(1024)	#receives the request message from the client

				#open file
				#read whole file and store the contents of the file to outputdata

        # STUDENT WORK

		filename = message.split(' ')[1][1:]		#split to find file extension
		#f = open(filename, 'rb')
		#outputdata = f.read()
		if( filename == 'favicon.ico'):				#if no filename it goes to favicon.ico, we change to index.html
			filename = 'index.html'
		try:
			file_extension = filename.split('.')[1]
			print(file_extension)
		except IndexError:						#if no
			file_extension = 'html'
		try:
			if (file_extension == 'html'):
				response_headers =  'Content-Type: text/html; encoding=utf8' 
			elif (file_extension == 'jpg'):
				response_headers =  'Content-Type: image/jpeg; encoding=utf8'
			else:
				print 'Invalid file type, we only support html and jpg!'
				continue
			f = open(filename, 'rb')
			outputdata = f.read()
			response_headers = 'HTTP/1.1 200 OK\nServer: Server\n' + response_headers
			contentlength = len(outputdata)
			print(contentlength)
			response_headers = response_headers + '\nContent-Length: ' + str(contentlength) + '\n'
			final = response_headers + '\n' + outputdata			
			print(final)
			#print(outputdata)

			#connectionSocket.sendall(response_headers)
			connectionSocket.send(final)

			#f.close()
			#connectionSocket.close()
			
            
            
        #Raised when an I/O operation (such as a print statement, the built-in open() function or a method of a file object) fails for an I/O-related reason, e.g., "file not found" or "disk full"
		except IOError:
			print 'File not found!'
			f = open('error.html', 'rb')
			outputdata = f.read()
			contentlength = len(outputdata)
			response_headers = response_headers + str(contentlength) + '\n'
   		
			connectionSocket.sendall(response_headers)
			connectionSocket.sendall(outputdata)

			f.close()
			connectionSocket.close()
			
# STUDENT WORK

print('test\n')
