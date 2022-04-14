#!python3
# -- coding: UTF-8 --
import re
import urllib.request, urllib.error
import bs4

url = "https://ctj12461.vercel.app/contents/20220404-multigenerator-document/"  # 地址
savePath = "/home/paperdog/HAHA/"
saveFile = "solution.md"


def code(x):
    return "\n```{}\n{}\n```\n".format(x.group("b"), x.group("a"))


def code_unknown(x):
    return "\n```\n{}\n```\n".format(x.group("a"))


def image(x):
    y = x.group("a")
    a = re.search(
        r'src="(?P<a>((http|https):\/\/)?(\w|\.|-)*(\/(\w|\.|-|&|#|%|=|\?)*)*)"', y
    ).group("a")
    b = re.search(
        r'alt="(?P<a>((http|https):\/\/)?(\w|\.|-)*(\/(\w|\.|-|&|#|%|=|\?)*)*)"', y
    ).group("a")
    return "![{}]({})".format(b, a)


def link(x):
    return "[{}]({})".format(x.group("b"), x.group("a"))


def get_html(url):
    headers = {
        "user-agent": "Mozilla / 5.0(Windows NT 10.0;Win64;x64) AppleWebKit / 537.36(KHTML, likeGecko) Chrome / 85.0.4183.121 Safari / 537.36"
    }
    request = urllib.request.Request(url=url, headers=headers)
    response = urllib.request.urlopen(request)
    html = response.read().decode("utf-8")
    if str(html).find("404 robot") == -1:  # 博客园中没找到该题目或无权查看的提示网页中会有该字样
        return html
    else:
        return "error"


def get_markdown(html):
    bs = bs4.BeautifulSoup(html, "html.parser")
    core = bs.find_all("div", class_="article-entry marked-body js-toc-content")[0]
    md = str(core)
    md = re.sub(
        r'<pre><code\sclass="language-(?P<b>[^"]*)">(?P<a>[^<]*)</code></pre>',
        code,
        md,
        0,
        re.M,
    )
    md = re.sub(
        r"<pre><code>(?P<a>[^<]*)</code></pre>",
        code_unknown,
        md,
        0,
        re.M,
    )
    md = re.sub("(?P<a><img[^>]*>)", image, md, 0, re.M)
    md = re.sub('<\w\shref="(?P<a>[^"]*)"[^>]*>(?P<b>[^<"]*)</\w>', link, md, 0, re.M)
    md = re.sub("</?code>", "`", md, 0, re.M)
    md = re.sub("</?strong>", "**", md, 0, re.M)
    md = re.sub("</?s>", "~~", md, 0, re.M)
    md = re.sub("</?em>", "*", md, 0, re.M)
    md = re.sub("<h1[^>]*>", "\n# ", md, 0, re.M)
    md = re.sub("<h2[^>]*>", "\n## ", md, 0, re.M)
    md = re.sub("<h3[^>]*>", "\n### ", md, 0, re.M)
    md = re.sub("<h4[^>]*>", "\n#### ", md, 0, re.M)
    md = re.sub("<h5[^>]*>", "\n##### ", md, 0, re.M)
    md = re.sub("<h6[^>]*>", "\n###### ", md, 0, re.M)
    md = re.sub("</h[0-6]*[^>]*>", "\n", md, 0, re.M)
    md = re.sub("<li>", "- ", md, 0, re.M)
    md = re.sub("<li>\n", "1. ", md, 0, re.M)
    md = re.sub("</?[a-zA-Z]+[^<>]*>", "", md, 0, re.M)
    md = re.sub("&lt;", "<", md, 0, re.M)
    md = re.sub("&gt;", ">", md, 0, re.M)
    md = re.sub("&amp;", "&", md, 0, re.M)
    md = re.sub(r"\\\(", " $", md, 0, re.M)
    md = re.sub(r"\\\)", "$ ", md, 0, re.M)
    md = re.sub(r"\\\[", "$$", md, 0, re.M)
    md = re.sub(r"\\\]", "$$", md, 0, re.M)
    return md


def save_data(data, filename):
    cfilename = savePath + filename
    file = open(cfilename, "w", encoding="utf-8")
    for d in data:
        file.writelines(d)
    file.close()


if __name__ == "__main__":
    print("计划爬取到{}".format(url))
    print("正在爬取{}...".format(url), end="")
    html = get_html(url)
    if html == "error":
        print("爬取失败，可能是不存在该题或无权查看")
    else:
        problemMD = get_markdown(html)
        print("爬取成功！正在保存...")
        save_data(problemMD, saveFile)
        print("保存成功!")
    print("爬取完毕")
