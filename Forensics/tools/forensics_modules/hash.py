def get_hashes(filepath, chunk_size):
    import hashlib
    hash_sha256 = hashlib.sha256()
    hash_md5 = hashlib.md5()
    data = True
    with open(filepath, "rb") as source:
        while data:
            data = source.read(chunk_size)
            hash_sha256.update(data)
            hash_md5.update(data)
        source.close()

    return {"md5": hash_md5.hexdigest(), "sha256": hash_sha256.hexdigest()}
