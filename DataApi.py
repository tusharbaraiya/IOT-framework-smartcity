import MySQLdb

dbase = ""

db = MySQLdb.connect(host="localhost",
                     user="root",
                     passwd="",
                     db=dbase)
cur = db.cursor()

def init_connection(dbs):
    global db,cur
    db = MySQLdb.connect(host="localhost",
                         user="root",
                         passwd="",
                         db=dbs)
    cur = db.cursor()


def get_data(device, sensor):
    cur.execute("SELECT " +sensor+ " FROM "+device)
    l = [i for sub in cur.fetchall() for i in sub]
    return l

