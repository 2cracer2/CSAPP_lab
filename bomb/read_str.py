

s = []
with open("./bomb", "rb") as f:
    f.seek(0x2400)
    for i in range(100):
        s.append(f.read(1))
        if s[-1] == 00:
            break
    print(s)
        