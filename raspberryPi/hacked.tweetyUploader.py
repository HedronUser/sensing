#dante crapped up version
#my server ip address, username and password

#changed to allow port number to be specified
#changed to archive the files rather than delete files (os.rename)

import time
from ftplib import FTP
import glob
import os

pollingIntervalSeconds = 5
uploadHost = "10.0.0.110"
uploadUsername = "dante550"
uploadPassword = "ctldemo"
uploadPort = "2121"
uploadDir = './'
allWavs="*.wav"

previousFiles={}

# overall logic:
# we poll the local filesystem for .wav files
#   when we find a new one, we store its size in the
#   *previousFiles* dictionary.
#   if we find a local file whose name is in the dictionary,
#   we check if the file size has changed
#     if it has changed, we update the size in the dictionary
#     if it has not changed, we upload it:
#       connect to the FTP server212
#       change to the upload directory
#       store the file to the FTP server
#       check the FTP server's size for the file
#       if it matches, we delete the local file
#       if it doesn't match, we need to delete the old one TODO
# and loop
while True:
    wavFiles=glob.glob(allWavs)
    for wavName in wavFiles:
        wavSize = os.path.getsize(wavName)
        if wavName in previousFiles:
            if wavSize == previousFiles[wavName]:
                print("uploading {}".format(wavName))
                ftp = FTP() # , uploadUsername, uploadPassword)
		ftp.connect(uploadHost,uploadPort)
                ftp.login(uploadUsername, uploadPassword)
                ftp.cwd(uploadDir)
                wavFile = open(wavName, 'rb')
                resp = ftp.storbinary('STOR {}'.format(wavName), wavFile)
                wavFile.close()
                # TODO: check resp for OK
                remotes = []
                resp = ftp.retrlines('LIST {}'.format(wavName), remotes.append)
                # TODO: check resp for OK
                if len(remotes) > 0:
                    remoteElts = remotes[0].split()
                    # example:
                    # ['-rw-r--r--', '1', '504', '80', '8', 'Jan', '27', '18:15', 'hello.txt']
                    remoteSize = int(remoteElts[4])
                    if remoteSize == wavSize:
                        print("successfully uploaded {}, removing local".format(wavName))
                        del previousFiles[wavName]
                        #os.remove(wavName)
			wavDest = "./Archive/" + wavName
			
                        os.rename(wavName, wavDest)
                    else:
                        # TODO: we have a problem -- need to delete
                        # the partial upload.
                        print("couldn't upload {}, {} != {}".format(
                                    wavName, remoteSize, wavSize))
                ftp.close()
            else:
                print("old file {} new size: {}".format(wavName, wavSize))
                previousFiles[wavName] = wavSize
        else: # if wavName in previousFiles:
            print("found new file {} size: {}".format(wavName, wavSize))
            previousFiles[wavName] = wavSize

    print("done this time, sleeping")
    time.sleep(pollingIntervalSeconds)
