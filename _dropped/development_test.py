import pymongo

client = pymongo.MongoClient('mongodb://localhost:27017/')
db = client.noname_db
collection = db.camera_credentials

# print(collection.count_documents({"user": b"admin"}))
#
# for _ in collection.count_documents({"user": b"admin"}):
#     print(_)

pipeline = [
    {
        "$group": {
            "_id": "$ipport",
            "user": {"$push": "$user"},
            "pwd": {"$push": "$pwd"}
        }
    }
]

for _ in collection.aggregate(pipeline):
    print(_)
