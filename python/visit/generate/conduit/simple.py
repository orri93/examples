import conduit

n = conduit.Node()
n["my"] = "data"
n["a/b/c"] = "d"
n["a"]["b"]["e"] = 64.0
print(n)

print("total bytes: %d" % n.total_strided_bytes())
