 v4 
         git config --global user.name "Your Name"
         git config --global user.email "your_email@example.com"
git init
git remote add origin git@github.com:YourUsername/YourRepository.git
         ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
         eval $(ssh-agent -s)
         ssh-add ~/.ssh/id_rsa
         cat ~/.ssh/id_rsa.pub
echo "# My Project" >> README.md
git checkout -b v1
git add .
git commit -m "Your commit message"
git push origin v1
缩进代表可以不用配置

