#!python3
# -- coding: UTF-8 --
import re
import urllib.request, urllib.error
import bs4

def code(x):
    return '\n```{}\n{}\n```\n'.format(x.group('b'),x.group('a'))
def code_unknown(x):
    return '\n```\n{}\n```\n'.format(x.group('a'))

def image(x):
    y = x.group('a')
    a = re.search(r'src="(?P<a>((http|https):\/\/)?(\w|\.|-)*(\/(\w|\.|-|&|#|%|=|\?)*)*)"',y).group('a')
    b = re.search(r'alt="(?P<a>((http|https):\/\/)?(\w|\.|-)*(\/(\w|\.|-|&|#|%|=|\?)*)*)"',y).group('a')
    return "![{}]({})".format(b,a)
    
def link(x):
    return "[{}]({})".format(x.group('b'),x.group('a'))

def get_markdown(md):
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

def parse_url(html):
    bs = bs4.BeautifulSoup(html, "html.parser")
    core = bs.find_all("iframe")[0]
    return "https://vjudge.csgrandeur.cn" + re.search('src="(?P<a>[^"]*)"',str(core),re.M).group('a')
