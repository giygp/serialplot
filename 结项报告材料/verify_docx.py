import glob
import re
import sys

import docx

sys.stdout.reconfigure(encoding="utf-8")

for path in sorted(glob.glob(r"D:\结项报告书\*.docx")):
    print("=" * 30)
    print(path)
    d = docx.Document(path)
    paras = [p.text.strip() for p in d.paragraphs if p.text.strip()]
    import os
    base = os.path.basename(path)
    if "结项报告" in base and "申请书" not in base:
        chapters = [t for t in paras if re.match(r"^[一二三四五]、", t)]
        print("章节数:", len(chapters), chapters)
        figs = [t for t in paras if re.match(r"^图\s*\d+", t)]
        print("图注:", figs)
        print("表格数(截图占位框):", len(d.tables))
    else:
        print("段落数:", len(paras))
        if d.tables:
            t = d.tables[0]
            print("表格数:", len(d.tables), "首表列数:", len(t.columns), "行数:", len(t.rows))
            print("表头:", [c.text.strip() for c in t.rows[0].cells])
