
# Behnam Dezfouli
#  CSEN, Santa Clara University

# This program implements a simple smtp mail client to send an email to a local smtp server

# Note:
# Run a local smtp mail server using the following command before running this code:
# python -m smtpd -c DebuggingServer -n localhost:6000


from socket import *
import ssl


# Choose a mail server
mailserver = 'localhost'


# Create socket called clientSocket and establish a TCP connection with mailserver
clientSocket = socket(AF_INET, SOCK_STREAM)
# Port number may change according to the mail server
port = 6000
server_address = (mailserver, port)
clientSocket.connect(server_address)

recv = clientSocket.recv(1024).decode()
print(recv)
if recv[:3] != '220':
    print('220 reply not received from server.')


# Send HELO command along with the server address
msg = "HELO localhost:6000\r\n"
msg = msg.encode()
clientSocket.send(msg)

recv = clientSocket.recv(1024).decode()
print(recv)

# Send MAIL FROM command and print server response
msg = "MAIL FROM: jling@localhost.com\r\n"
msg = msg.encode()
clientSocket.send(msg)

recv = clientSocket.recv(1024).decode()
print(recv)

# Send RCPT TO command and print server response
msg = "RCPT TO: tenkhjargal@localhost.com\r\n"
msg = msg.encode()
clientSocket.send(msg)

recv = clientSocket.recv(1024).decode()
print(recv)

# Send DATA command and print server response
msg = "DATA\r\n"
msg = msg.encode()
clientSocket.send(msg)

recv = clientSocket.recv(1024).decode()
print(recv)


# Send message data.
msg = "Hello Tamir!\nThis is Lab 5!\n The Career Fair really took a toll on our labs huh?\n Goodbye!\r\n"
msg = msg.encode()
clientSocket.send(msg)

msg = "\r\n.\r\n"
msg = msg.encode()
clientSocket.send(msg)

recv = clientSocket.recv(1024).decode()
print(recv)
# Message to send
# Message ends with a single period
# Send QUIT command and get server response
msg = "QUIT\r\n"
msg = msg.encode()
clientSocket.send(msg)

recv = clientSocket.recv(1024).decode()
print(recv)

