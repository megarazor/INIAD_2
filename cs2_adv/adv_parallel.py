import numpy as np
import os
import platform as pl
import logging
import hashlib
with open('adv302.log', mode='w') as f:
    f.write('--begin--\n')
logging.basicConfig(filename='adv302.log', filemode='a', level=logging.DEBUG, format='%(asctime)s %(message)s')
from numpy.distutils.system_info import get_info
ob_dir=get_info('blas_opt')['library_dirs'][0]
ob_file=get_info('blas_opt')['libraries'][0]
if os.sys.platform == 'linux':
  ob_path=ob_dir+'/lib'+ob_file+'.so'
elif os.sys.platform == 'win32':
  ob_path=ob_dir+'/'+ob_file+'.dll'
elif os.sys.platform == 'darwin':
  ob_path='lib'+ob_file+'.dylib'
else:
  print('Write some code for '+os.sys.platfrorm)
  raise
un='{} {} {} {}'.format(pl.system(),pl.node(),pl.release(),pl.machine())
logging.info(ob_path)
import time
import ctypes
try:
  ob_lib=ctypes.cdll.LoadLibrary(ob_path)
  logging.info('Opt BLAS found')
except OSError:
  logging.info('Opt BLAS not found')
  raise

N=6000
x=np.random.rand(N*N).astype(np.float32).reshape((N,N))
logging.info("{0:.1f} MB".format(x.nbytes/1024/1024))
logging.info('Number of threads: {0}'.format(ob_lib.mkl_get_max_threads()))
logging.info('{0}*{0} matmul'.format(N))

for i in range(1,ob_lib.mkl_get_max_threads()+1):
  ob_lib.mkl_set_num_threads( ctypes.byref(ctypes.c_int(i)))
  tm = time.perf_counter()
  np.dot(x, x)
  tm = time.perf_counter() - tm
  if i == 1:
    tm1 = tm
    logging.info('{0} threads {1:.3f} sec'.format(i,tm))
  else:
    logging.info('{0} threads {1:.3f} sec {2:.2f}x speedup'.format(i,tm,tm1/tm))

logging.shutdown()

with open('adv302.log') as f:
    d=f.read()
    h=hashlib.sha256(d.encode()).hexdigest()
with open('adv302.log', mode='a') as f:
    f.write(h)
    f.write('\n')
    f.write('--end--\n')
