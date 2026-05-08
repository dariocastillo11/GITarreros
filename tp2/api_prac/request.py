import requests
res = requests.get('https://scotch.io')
if res:
	print('Response OK')
else:
	print('Response Failed')
print(res.status_code)
print(res)
print(res.text)
