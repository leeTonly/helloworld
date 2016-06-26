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



