var spawn = require('child_process').spawn

var ps = spawn('grep', ['potatoe'])
ps.stdout.pipe(process.stdout)

ps.stdin.write('abc\n')
ps.stdin.write('potatoe-flavoured chips\n')
ps.stdin.write('def\n')
ps.stdin.write('potatoe\n')
ps.stdin.end()

