# Data repository for 'Predicting battery end of life from solar off-grid system field data using machine learning'

A pre-print of the publication that refers to this data may be found at [https://arxiv.org/abs/2107.13856](https://arxiv.org/abs/2107.13856). This repository contains the raw data used in the research. The three sets of files are:

1. Telemetry data from 1027 BBOXX valve-regulated lead-acid battery systems in the field. These are split into 10 zip files, containing ~100 .npz (compressed python format) files each. Following download, the tool **zip_to_npy.py** may be run in Python to extract all the files. The resulting npy files may then be used for analysis. The telemetry data contains an average of ~600'000 data rows for each battery, where each row consists of a UNIX timestamp and then measured current (where negative current is charging), voltage and temperature readings. The recording frequency is non-uniform in time.

2. Data from open circuit voltage (OCV) lab tests using a Biologic SP-150 potentiostat **GITT_OCV.mpt**. This data is used to determine the OCV @ 25 degC of the lead-acid battery used in the research, as described in the supplementary materials of the paper.

3. Metadata for the field batteries. The columns in the file **meta_data.csv** consist of the battery UID, followed by the activation date, repair date, lifetime in days and a boolean flag indicating whether the battery in question entered repair. Note that if the flag is false, there is no repair date and the battery lifetime, in this case, is the date difference from the activation date to the final date in the datasample.

**Please see the included license file, also repeated below**

******************************************************************************************
These data are copyright (c) 2021, BBOXX Ltd., The Chancellor, Masters and Scholars of the University of Oxford, and the 'Predicting battery end of life from solar off-grid system field data using machine learning' researchers. All rights reserved.

This 'Predicting battery end of life from solar off-grid system field data using machine learning' data is made available under 
a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.
<br />
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br />


THIS DATA IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS DATA, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
