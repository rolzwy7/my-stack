#python3

import poplib
from email import parser

conn = poplib.POP3_SSL('pop.gmail.com', '995')
conn.user('username')
conn.pass_('password') # or google application-pass

for i in range(1, len(conn.list()[1])+1):
    tmp = conn.retr(i)
    joined = b"\n".join(tmp[1])
    try:
        message = parser.Parser().parsestr(str(joined, "utf8"))
    except Exception as e:
        print("[-]", "Exception:", e)
        continue
    print("-"*64)
    print("From    : ", message["From"]) # for more -> 'message.keys()'
    print("To      : ", message["To"])
    print("Subject : ", message["Subject"])

pop_conn.quit()
