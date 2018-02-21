import time
import paramiko
import glob
import os

pollingIntervalSeconds = 5
uploadHost = "fill me in"
uploadUsername = "tweetyuser"
uploadPassword = "fill me in"
uploadDir = 'upload'
uploadPort = 2222
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
#       connect to the FTP server
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
                transport = paramiko.Transport((uploadHost, uploadPort))
                transport.connect(username=uploadUsername, password=uploadPassword)
                sftp = paramiko.SFTPClient.from_transport(transport)
                sftp.chdir(uploadDir)
                wavFile = open(wavName, 'rb')
                resp = sftp.put(wavName, wavName)
                wavFile.close()
                # TODO: check resp for OK
                try:
                    resp = sftp.stat(wavName)
                    # example:
                    remoteSize = resp.st_size
                    if remoteSize == wavSize:
                        print("successfully uploaded {}, removing local".format(wavName))
                        del previousFiles[wavName]
                        os.remove(wavName)
                    else:
                        # TODO: we have a problem -- need to delete
                        # the partial upload.
                            print("couldn't upload {}, {} != {}".format(
                                    wavName, remoteSize, wavSize))
                except FileNotFoundError:
                    pass
                # todo - do something better
                sftp.close()
                transport.close()
            else:
                print("old file {} new size: {}".format(wavName, wavSize))
                previousFiles[wavName] = wavSize
        else: # if wavName in previousFiles:
            print("found new file {} size: {}".format(wavName, wavSize))
            previousFiles[wavName] = wavSize

    print("done this time, sleeping")
    time.sleep(pollingIntervalSeconds)
