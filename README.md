###1. git init
lee@lee-W675SJ:~/Coding/git_helloworld$ git init
初始化空的 Git 仓库于 /home/lee/Coding/git_helloworld/.git/


###2. ssh-keygen -t rsa -C "772662623@qq.com"
lee@lee-W675SJ:~/.ssh$ ssh-keygen -t rsa -C "772662623@qq.com"
Generating public/private rsa key pair.
Enter file in which to save the key (/home/lee/.ssh/id_rsa): 
/home/lee/.ssh/id_rsa already exists.
Overwrite (y/n)? y
Enter passphrase (empty for no passphrase): 
Enter same passphrase again: 
Your identification has been saved in /home/lee/.ssh/id_rsa.
Your public key has been saved in /home/lee/.ssh/id_rsa.pub.
The key fingerprint is:
SHA256:T/cw6eNXuRpiSwoghKkAdpmTUxDNn3HY1EDdnKeHLBE 772662623@qq.com
The key's randomart image is:
+---[RSA 2048]----+
|.. +X.  =++E+ .  |
|o +* o o o + + . |
|.o .o . +   o +  |
|o .    o   . = . |
|.  . .  S . * . .|
|    . .  o o + ..|
|       .  .+o....|
|        . +.o.o. |
|         . ..o.  |
+----[SHA256]-----+


###3. cat ~/.ssh/id_rsa.pub
然后将打印出来的值添加在github的SSH里。


###4. ssh -T git@github.com
检验ssh，如果提示Permission denied，则还要执行下面语句
lee@lee-W675SJ:~/Coding/git_helloworld$ ssh -T git@github.com
sign_and_send_pubkey: signing failed: agent refused operation
Permission denied (publickey).
lee@lee-W675SJ:~/Coding/git_helloworld$ eval "$(ssh-agent -s)"
Agent pid 16554
lee@lee-W675SJ:~/Coding/git_helloworld$ ssh-add
Identity added: /home/lee/.ssh/id_rsa (/home/lee/.ssh/id_rsa)
lee@lee-W675SJ:~/Coding/git_helloworld$ ssh -T git@github.comHi leeTonly! You've successfully authenticated, but GitHub does not provide shell access.


###5. 同步代码库。
lee@lee-W675SJ:~/Coding/git_helloworld$ git clone git@github.com:leeTonly/helloworld.git
正克隆到 'helloworld'...
remote: Counting objects: 10, done.
remote: Compressing objects: 100% (9/9), done.
remote: Total 10 (delta 1), reused 0 (delta 0), pack-reused 0
接收对象中: 100% (10/10), 12.82 KiB | 0 bytes/s, 完成.
处理 delta 中: 100% (1/1), 完成.
检查连接... 完成。

###6. 配置git
lee@lee-W675SJ:~/Coding/git_helloworld$ git config --global user.name lee
lee@lee-W675SJ:~/Coding/git_helloworld$ git config --global user.email 772662623@qq.com
lee@lee-W675SJ:~/Coding/git_helloworld$ git config --global github.user leeTonlylee@lee-W675SJ:~/Coding/git_helloworld$ git config --global github.token 7e09ba0452a1991253e34990ae3c66a61f8e0bc4

lee@lee-W675SJ:~/Coding/git_helloworld$ git remote add origin git@github.com:leeTonly/helloworld.git


###7. 上传代码
lee@lee-W675SJ:~/Coding/git_helloworld$ git add git的使用方法.c 
lee@lee-W675SJ:~/Coding/git_helloworld$ git commit -m git的使用方法.c 
[master （根提交） 7fb7f0c] git的使用方法.c
 1 file changed, 50 insertions(+)
 create mode 100644 "git\347\232\204\344\275\277\347\224\250\346\226\271\346\263\225.c"

lee@lee-W675SJ:~/Coding/git_helloworld/helloworld$ git push origin master
对象计数中: 2, 完成.
Delta compression using up to 8 threads.
压缩对象中: 100% (2/2), 完成.
写入对象中: 100% (2/2), 204 bytes | 0 bytes/s, 完成.
Total 2 (delta 1), reused 0 (delta 0)
To git@github.com:leeTonly/helloworld.git
   45b7913..6a3c99e  master -> master


###8. 更新代码
lee@lee-W675SJ:~/Coding/git_helloworld/helloworld$ git push origin master
对象计数中: 3, 完成.
Delta compression using up to 8 threads.
压缩对象中: 100% (2/2), 完成.
写入对象中: 100% (3/3), 246 bytes | 0 bytes/s, 完成.
Total 3 (delta 1), reused 0 (delta 0)
To git@github.com:leeTonly/helloworld.git
   568c8e5..45b7913  master -> master


###9. 删除代码
lee@lee-W675SJ:~/Coding/git_helloworld/helloworld$ git rm 1111 
rm '1111'
lee@lee-W675SJ:~/Coding/git_helloworld/helloworld$ git commit -m 1111
[master 6a3c99e] 1111
 1 file changed, 0 insertions(+), 0 deletions(-)
 delete mode 100644 1111
lee@lee-W675SJ:~/Coding/git_helloworld/helloworld$ git push origin master
对象计数中: 2, 完成.
Delta compression using up to 8 threads.
压缩对象中: 100% (2/2), 完成.
写入对象中: 100% (2/2), 204 bytes | 0 bytes/s, 完成.
Total 2 (delta 1), reused 0 (delta 0)
To git@github.com:leeTonly/helloworld.git
   45b7913..6a3c99e  master -> master


###9. 同步代码
lee@lee-W675SJ:~/Coding/git_helloworld$ git pull git@github.com:leeTonly/helloworld.git
来自 github.com:leeTonly/helloworld
 * branch            HEAD       -> FETCH_HEAD
Merge made by the 'recursive' strategy.
 LICENSE   | 674 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 README.md |   1 +
 2 files changed, 675 insertions(+)
 create mode 100644 LICENSE
 create mode 100644 README.md

以后就可以直接用git pull了。





