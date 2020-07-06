
# Behnam Dezfouli
#  CSEN, Santa Clara University

# This program implements a simple smtp mail client to send an email to a local smtp server
# the program runs the ping command, and emails the result using smtp.gmail.com

# NOTE: Do not forget to allow login from less secure apps in your gmail account. Otherwise gmail will complain about username and password.


import smtplib, ssl
import subprocess
import os
from email.mime.text import MIMEText

port = 465  # For SSL
email_address = raw_input("Enter your email address: ")
password = raw_input("Enter your password: ")
receiver_email = raw_input("Enter receiver's email address: ")


# ping google.com and save the result
hostname = "google.com" #pinging Google.com
ping = subprocess.Popen(["ping", "-c", "2", hostname], stdout = subprocess.PIPE).stdout.read()


print ("\nNow contacting the mail server...")
server = smtplib.SMTP_SSL('smtp.gmail.com', port)
server.ehlo()

print ('\nSending email...')

subject = "Server Ping Result! Justin Ling"

text = "Hello,\nI have pinged google.com and the result is attached to this email:\n\n" + ping

msg = 'subject: {}\n\n{}'.format(subject, text)

server.login(email_address,password)
send_it = server.sendmail(email_address, receiver_email, msg)
server.quit()
