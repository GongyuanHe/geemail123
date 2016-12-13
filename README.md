# geemail

1.Command for code, you may need to install the crypto++ library.

g++ -o check_login check_login.cpp -lsqlite3 -lgcrypt    
./check_login [username] [passwd]


g++ -o register register.cpp -lsqlite3 -lgcrypt
./register [username] [passwd]

g++ -I/usr/local/include/cryptopp -o write_message write_message.cpp -lgcrypt -lsqlite3 -lcryptopp
./write_message [sender] [receiver] ['message'] ['passphrase']

g++ -I/usr/local/include/cryptopp -o read_message read_message.cpp -lgcrypt -lsqlite3 -lcryptopp
./read_message [message_id] ['passphrase']


2. This gee-mail has web user interface which is written in php.
There might be some problem when you run the web on your local host because our implementation achieved in cloud service.
To make this work, you need to modify the url which is like ' window.location.assign("https://geemail-cloned-parkhe.c9users.io/register.php"); '.

