import glob, os, sys,subprocess,cPickle
import commands
import time
import random


#__________________________________________________________
def getCommandOutput(command):
    p = subprocess.Popen(command, shell = True, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    stdout,stderr = p.communicate()
    return {"stdout":stdout, "stderr":stderr, "returncode":p.returncode}


#__________________________________________________________
def SubmitToBatch(cmd,nbtrials):
    submissionStatus=0
    for i in range(nbtrials):            
        outputCMD = getCommandOutput(cmd)["stderr"].split('\n')
        for line in outputCMD :
            if line=="":
                print "------------GOOD SUB"
                submissionStatus=1
                break
            else:
                print "++++++++++++ERROR submitting, will retry"
                print "Trial : "+str(i)+" / "+str(nbtrials)
                time.sleep(10)
                break
            
        if submissionStatus==1:
            return 1
        
        if i==nbtrials-1:
            print "failed sumbmitting after: "+str(nbtrials)+" trials, will exit"
            return 0

#__________________________________________________________
if __name__=="__main__":
    Dir = os.getcwd()
    
    from optparse import OptionParser
    parser = OptionParser()

    parser.add_option ('-n','--njobs', help='Number of jobs to submit',
                       dest='njobs',
                       default='10')

    parser.add_option ('-e','--energy', help='Gun energy. Defaul is 100',
                       dest='energy',
                       default='100')

    parser.add_option ('-u','--unit', help='Energy unit [MeV, GeV, TeV, ...] default is GeV',
                       dest='unit',
                       default='GeV')

    parser.add_option ('-p','--particle', help='Particle type [e-, mu-, pi-, etc...] default is mu-',
                       dest='particle',
                       default='mu-')

    parser.add_option ('-f', '--events',  help='Number of event per job. default is 100',
                       dest='events',
                       default='100')

    parser.add_option ('-t', '--threads',  help='Number of threads. default is 1',
                       dest='threads',
                       default='1')

    parser.add_option ('-m', '--mode',  help='Running mode [batch, local]. Default is batch',
                       dest='mode',
                       default='batch')


    (options, args) = parser.parse_args()
    njobs    = int(options.njobs)
    energy   = float(options.energy)
    unit     = options.unit
    particle = options.particle
    events   = int(options.events)
    threads  = int(options.threads)
    mode     = options.mode
 
    rundir = os.getcwd()
    nbjobsSub=0
    for i in xrange(njobs):
        fmacname = 'FCC_job%i_%s_%i%s.mac'%(i,particle.replace('+','plus').replace('-','minus'),int(energy),unit)
        fmac = open('tmp/'+fmacname, 'w')
        fmac.write('/gun/energy %f %s\n'%(energy,unit))
        fmac.write('/gun/particle %s\n'%(particle))
        fmac.write('/analysis/setFileName FCC_job%i_%s_%i%s\n'%(i,particle.replace('+','plus').replace('-','minus'),int(energy),unit))
        fmac.write('/random/setSeeds %i %i\n'%(i+1, i+2))
        fmac.write('/run/beamOn %i\n'%(events))
        fmac.write('exit\n')

        

        frunname = 'toRunFCC_job%i_%s_%i%s.sh'%(i,particle.replace('+','plus').replace('-','minus'),int(energy),unit)
        frun = open('tmp/'+frunname, 'w')
        commands.getstatusoutput('chmod 777 tmp/%s'%(frunname))


        if mode=='batch':
            frun.write('cd /afs/cern.ch/user/h/helsens/FCCsoft/FCCSOFT/FCC/FCCSW-hh/examples/Containment/\n')
            frun.write('LOCALDIR=$PWD \n')
            frun.write('source /afs/cern.ch/sw/lcg/external/gcc/4.7/x86_64-slc6-gcc47-opt/setup.sh /afs/cern.ch/sw/lcg/external\n')
            frun.write('cd /afs/cern.ch/sw/lcg/external/geant4/10.0.p02/x86_64-slc6-gcc47-opt-MT/bin\n')
            frun.write('source geant4.sh \n')
            frun.write('cd $LOCALDIR \n')
            frun.write('XERCESClibs=/afs/cern.ch/sw/lcg/external/XercesC/3.1.1p2/x86_64-slc6-gcc47-opt/lib/\n')
            frun.write('Geant4libs=/afs/cern.ch/sw/lcg/external/geant4/10.0.p02/x86_64-slc6-gcc47-opt-MT/lib64/\n')
            frun.write('CLHEPlibs=/afs/cern.ch/sw/lcg/external/clhep/2.1.4.1/x86_64-slc6-gcc47-opt/lib/\n')
            frun.write('export LD_LIBRARY_PATH=${Geant4libs}:${CLHEPlibs}:${XERCESClibs}:${LD_LIBRARY_PATH}\n')
            frun.write('cd build/\n')
            frun.write('./exampleFCC0 -i -t %i -m %s'%(threads,rundir+'/tmp/'+fmacname))
            cmdBatch = 'bsub -o %s -q 8nh %s/tmp/%s'%(frunname.replace('toRun','log').replace('.sh','.log'),rundir,frunname)
            print cmdBatch
            nbjobsSub+=SubmitToBatch(cmdBatch,10)


        elif mode=='local': 
            frun.write('./build/exampleFCC0 -i -t %i -m %s\n'%(threads,rundir+'/tmp/'+fmacname))
            #commands.getstatusoutput('./build/exampleFCC0 -i -t %i -m %s'%(threads,rundir+'/tmp/'+fmac))
            os.system('./build/exampleFCC0 -i -t %i -m %s'%(threads,rundir+'/tmp/'+fmacname))
            #out = getCommandOutput('./build/exampleFCC0 -i -t %i -m %s'%(threads,rundir+'/tmp/'+fmac))["returncode"]
            #status = subprocess.call('./build/exampleFCC0 -i -t %i -m %s'%(threads,rundir+'/tmp/'+fmacname), shell=True, subprocess.CREATE_NEW_CONSOLE)

            #os.spawnl(os.P_NOWAIT,'./build/exampleFCC0 -i -t %i -m %s'%(threads,rundir+'/tmp/'+fmacname) )

            #os.system('. %s/tmp/%s > too.log'%(rundir,frunname))
            print '. %s/tmp/%s'%(rundir,frunname)
            #print status
        else: print 'unknow running mode: %s'%(mode)
    print 'succesfully sent %i  jobs'%nbjobsSub
