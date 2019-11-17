def escalona(s, f):
    start = s
    finish = f

    start_min = []
    finish_min = []

    start_org = []
    finish_org = []

    start_pivot = start[0]
    finish_pivot = finish[0]

    count = len(finish)

    while count > 0:
        n = 0
        for i in finish:
            if i <= finish_pivot:
                start_pivot = start[n]
                finish_pivot = i
                exc = n
            n += 1
        start_min.append(start_pivot)
        finish_min.append(finish_pivot)
        start.pop(exc)
        finish.pop(exc)
        count -= 1
        if count == 0:
            finish.append(1)
        start_pivot = 0
        finish_pivot = finish[0]
    start_org.append(start_min[0])
    finish_org.append(finish_min[0])
    j = 0
    for i in range(1, len(finish_min), 1):
        if start_min[i] > finish_org[j]:
            start_org.append(start_min[i])
            finish_org.append(finish_min[i])
            j += 1
    print(start_org)
    print(finish_org)
    return 0