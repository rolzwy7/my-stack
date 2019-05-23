from pymongo import MongoClient
from config import MongoDBconf


class MongoDB():

    def __init__(self):
        self.client = MongoClient(MongoDBconf["uri"])
        self.db = self.client[MongoDBconf["db_name"]]
        self.db_name = MongoDBconf["db_name"]
        # Hosts
        self._hosts = self.db.hosts

    def _insert_one(self, collection, fields, **kwargs):
        print(
            "[mongodb] Saving to %s/%s" % (
                self.db_name,
                collection._Collection__name)
            )
        for f in fields:
            if f not in kwargs.keys():
                kwargs[f] = ""
        try:
            return collection.insert_one(kwargs).inserted_id
        except Exception as e:
            raise

    def _count_documents(self, collection, filters, **kwargs):
        return collection.count_documents(filters)

    def insert_host(self, **kwargs):
        fields = ["address", "mac", "name", "os_name", "info", "comments"]
        return self._insert_one(self._hosts, fields, **kwargs)
