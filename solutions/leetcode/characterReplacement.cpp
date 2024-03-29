//
//  characterReplacement.cpp
//  leetcode
//
//  Created by  Song Ding on 10/23/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

/**
 424. Longest Repeating Character Replacement
 Medium

 732

 55

 Favorite

 Share
 Given a string s that consists of only uppercase English letters, you can perform at most k operations on that string.

 In one operation, you can choose any character of the string and change it to any other uppercase English character.

 Find the length of the longest sub-string containing all repeating letters you can get after performing the above operations.

 Note:
 Both the string's length and k will not exceed 104.

 Example 1:

 Input:
 s = "ABAB", k = 2

 Output:
 4

 Explanation:
 Replace the two 'A's with two 'B's or vice versa.
  

 Example 2:

 Input:
 s = "AABABBA", k = 1

 Output:
 4

 Explanation:
 Replace the one 'A' in the middle with 'B' and form "AABBBBA".
 The substring "BBBB" has the longest repeating letters, which is 4.
 */

namespace characterReplacement {
    class Solution {
    public:
        int characterReplacement(string s, int k) {
            int n = s.size();
            vector<int> cnt(26, 0);
            int maxCnt = 0, start = 0;
            for (int i = 0; i < n; ++i) {
                maxCnt = max(maxCnt, ++cnt[s[i]-'A']);
                if (maxCnt + k < i - start+1) {
                    --cnt[s[start] - 'A'];
                    ++start;
                }
            }
            return n - start;
        }
        int characterReplacement3(string s, int k) {
            vector<int> count(26, 0);
            int start = 0, maxCnt = 0, res = 0;
            for (int i = 0; i < s.size(); ++i) {
                maxCnt = max(maxCnt, ++count[s[i] - 'A']);
                while (i - start + 1 - maxCnt > k) {
                    --count[s[start] - 'A'];
                    ++start;
                }
                res = max(res, i - start + 1);
            }
            return res;
        }
        /**
         Hints: when replacing other letters with 'A', only
         counting the longest A substring.
         Iterate through to 'Z'
         
         Now for each letter, iterate through each position
         and count backwards to see how many consecutive letters
         a substring ending at the position can have.
         */
        int characterReplacement2(string s, int k) {
            int len = s.size();
            int gmax = k;
            if (k > len) {
                gmax = len;
            }
            for (int i = gmax; i < len; ++i) {
                int mismatches = 0;
                int j = i - 1;
                char c = s[i];
                for (; j >= 0; --j) {
                    if (s[j] != c) {
                        ++mismatches;
                        if (mismatches > k) {
                            break;
                        }
                    }
                }
                int t = i;
                if (mismatches < k) {
                    t += k - mismatches;
                    if (t >= len) {
                        t = len - 1;
                    }
                }
                if (gmax < t - j) {
                    gmax = t - j;
                }
            }
            return gmax;
        }
    };
}
/*
int main() {
    string s("WBRIQCVFYHTSFAJVVSUBLQYBSMUWULUKUAMUSDTVJRWSSYRXTSCIYUDTGOCWRJHBURWQYENEEYVCHVIKBYBQJUGRWVLFORNVSISGDNZREMWMUWXWWRMPBNZAPSFDSGVCGJPEDUCWBMGEZCWUVNKFTFONIKHWGYPFGMEIKMYFRVDDTPEZLUHZIHVKBWGMUUDYBTXZCIRVOAWZTSEZUTJNDXJSWXZZTXPNTCNDPPWLXEHJPZVKAYMHYDNQRMIPEIRJNGYZQCIQSWRQSLSFENBTEABYWJIQNDMQHXMWALFKQBFWWNKSVDIZHLSAQWEQKHFFOUECQVUDMYNFUYBMROIGKLKPYIWSBBORHGLQOTJSOOIABZAJVPDUHHHUIXQBCWVSMVGSOGDVDILBJEFNIPSNNODGTWFHCPYBETOEYXEUDHGJDYMUAXLSIHDCDBVZUWFOMKOJGWTXEPOSTTUXJATSJJACDQYBLWNWOAGZQEQQZKVEKMMYARXHQXRLNAUMPDFSCODEFPFVKIJRYFYNBNRAXGDIEWDPVCRPQRZKWUKKSGFHIVFVHSUEYALRENJVBEQINQASMBRXLRPKXNHCZRVMVSOSJDRJHZIWMCLOTKNYVTRDPNUEJLMIAHFLLWUQLUZQVDUBRAHJOFSSAMOJOAYLKEGCJGTRKHHRZJTTBLGCUMLTKILXNYOTGZQWCKOJLLVTGSSRHDPPRLMXFNILNJPHMIWJKKHJNJRLQTVFKBKAJZMDVTXPGXHOONEYUXVILSEGSJKHLHCFGCAZMWYXFUMNWHIYGZFRZPRJTVBEXCFFGULMZSDRZAVWUVDQCTXZBHFAPOZQCRKVHWWYEALJBYDGMIEEXDDFZYEBUHUEZMZALGZAHHAECPMEGDRMVZZNQRQULRNRABQUOIEGXLNOZUFQJKDKGCZFVIPBIRNQBEERWMTWUBIGFUHKRQVACWPGFHFAPFBZMQXEYGWRBWZEQEHXXCUAJWEECFNHXRWFQUPMOQEEZWRPRHILZVCCWDTFZETWABPEKWCBDIHEAZKVNQOOOGQVGHTTUFCAFWHMECOSZKTHQXPORBGXLVDETCBIDIOYSZNPOXUKHSFBLSWVBXQOPFSTLVQPSIKKGUFCDCKVBSMAAEGUDFUXJAFQYVVTKEEQUUXJQMSGXGWEUELFFFVEHRDPZKBVNUQZOTMXIZFXCURFDSWINGWIAPLHLXZDOMNMMSYNNKAFNGLVOBYERFMSGLNNFDXWGHKADQVLIQHITXFBYTORPZYBWQEBNTCETQHVLMCHDHNQEUQWLCGDKXUHSQIILMHVFQIJMWSEXTLNRWMRDUAEEHNYTCWKWIGRASCAVRBSZEYHJXXWQAILZXHZQNOEUQIYPGXRRMCAFBOPTQFJIDWUUIMTBESCAJYMPDJGPGHFEXLPGJLDJIWMROJISDHZUYOMWQEWYTPHDMYYUKZWZFIGOACLZVYMKTMAHHGNHRMFBLPDWUPVZXHJPJAAFYFGMSRSQKWXKOWMPNTZPUBYJYIPMRERSTWHEDSXXJGHHMWYRNBEGYVHUQVVELAORPJWLECIKPPPNTGCJFBJNZGXCCTUNOJMZLXDTIWDDHBMBXXUUMWNJSNPVPKKEDWRPIATEAVHFONBVYVWCSIYPKFCIIMXKPYWKCXLQGKQNXDKKHGSTIWAMGDLXJCYFQNOLKVRPBUMNTQYZHACFZFGGWQIJRSAVKDXHHKQODGBEBFLPIESJEQQFXOVXORDPREKPDHMYSXAQCSSBPIQTFJCDRDOFQUHHHJKIRAPJACSFWVUBDJMQBJFNFFXXSLOBJFTMBBILIBFQOUMCQXMQHXNICXDXYKXEAAHVYSUHAYQKEPLQXVJYFFNWZRXXVWUNTQGWYURBJIHTSPIMCVHXIQIGQZJAVNYIFRYNPNYMQNYBQIGFOYGHOZBBHDYQMSYPSMAXZOWMAGWVXDAXNCTBRLQPOTRSPUHWSXLJVRKRCBZRAYWZHAFZXONWTMNQDDYVZAPOPHUHOJGRSHBJLXLTOMRGJLZDBVTKIWJHAQXFXAZSANBVQCIYPLBSSYULGOARKRKDSHSWOYCAEQGWEZQXWHTWSHGVOBBKAYBUMJORLVAPLQZYVFIGREYEUGUHDJYCLVXFBURBPFRSFOISPTCTRFULTBZPBZNWRRWJXSYYEAAKCRNGNFWSZDFTUIZVNVYPDMGXATHULMMSLQQHYTWOOTIFJIERABJPAUQAQVFUBGIHJTBIVAFNALLKKGRCNIONHOATUZNROWTRJCYVYLCWCPDUQEBTERIBDARVZPQJBUUJOAIYPYIUWXFCAQOLEMWVEMUWXGSOZJRAAAUVDCODWQONAEBQKNPAPCBHCNQAVRCNOBWSPCKVSUQHHNWGUTIHUDCEKMLHOCWHMKPYBGTQYKXSSIAMBMKLWZMGQLNAMAUDKQZTNUTZJWBBQUTWAUQMQMXTJHERZGYIAOGHALPDUUXVAQJFTDWVLJAHDNGGHDELGPNUYJKGLFNUFVQOKXNDDIMLEWHOKPKLWSGTHBDQGQQIVTRKNSSLPVCQPGWZPLKMWTPWOMWCKLFKHDDOBOUQVHJENRGVJBNCJVJDQYEDBSVOEXPJVYYWIMVXLXAEVFHURSJIMNJQGVDSMREMQGOKXAFWMMFGSMZBIVGIOHWKCHYPDRQEUDFBDKQFQPOEILESIULDPSKYYOJYIQCKPZSIBPNQIZCWJHCUZSEJOXWGUKXPAWXJPSFFDPANHLEAXAUMOTOZTCNBSBPGLJSWJATQFOJTNGPCSGXOFYCSKBLALTPNVODVZSDLIYACERBYLACMDIESPMTFVBWGSYDOZXTTKVWXWGWBGAGNQLZNWWJFOTJRAOKHGRUTKFLRYUGOMHRSITXDJRSCRCDDRWKGVVXAUGPUUOPGSVXQSYAIUAQAKMZHRFHZZDTHRTRMFPGIWCZLSRIILSRMBRFSEMAVGLYVUAWQQCTEDUZDHCSMLUGDUVKUTPMIBYDEPNVPWUIZAZKEMOGRMLSITHOUYBZBJWTMYBXLETPBIXCJQFIPVXOPKEEVNTJFVTYUGBDQJGTQFKNNEFIPUTITZRJBEMQZEPISAZBYFIMKKOWFMTRMTJTWVWPLYOXSKJDZUXAATGIOZDLCPJEGPUTBYAHJGLTZTOSRZZPQGNUWPUBFYGSDVSSYKZEOGJZMFUYBFDPORSJEGZTDVURPTMMQNMNQVFHIDMPGVKQKZKXVDMAJXOGXAOJJNXSNEOBEWUXGWNLTXZZPFRJYQNJICGDEFDIUOGWAOVTAGXNDVJRPHMZOKRZYMMNFAXYPTYZXITXADXDGVHEBEACVLPSOTAMLIVPHCSJWQKTSTCYKWETJDOYBXCHWCLGLBUTEHTRIPFTSYTMHHMXJBLFMLMIDDBGAZWSKFTIBDOUHOYYKTRKKVDFTSMTJWAHYEICILPFUDZEYFZLFWDZIXFORJCJJDLSDDOKNXTNIJHBDYFPTMGOGNJQJHNJTOXGVYBMVPZIUCANUODRIFUDWRZFSMZVHECLCHBVQWZSGOETPZHTPEYIYGDKERGBQMTTBAJVEIECMORZBWAOOVNTINTZIFPDOVSCFMUAGNGLVRZMUAHNEAFJNVPJUJWNENIMZMHQLXQTHDKZFTNISFGTNFNPKRDPBOEVPVNMRXRIQYZIBFAPMOHWOEXIEHSKABDTZDLBXCJJLZILVJBJCJGFPGBFZFNXDBUJWYSNYAUEQXTRDGUUKPHFKGQFNZUNWMIMJMROSPRZZIFVELXRWDZMDMYCDQEJYVZULVZCDPZGTPBFQORXGFPSOKMCHWMCLKOVPTRUBWETSPSBZKVREMQEIPTNQICTASVIHWROEZJNCFIQKBFNNABJGKWCSSBYMBOIKCADMOTWDBWAGXFDPMCLUURSQMMCVLBJZQAYUWNDYWBRAMSRPURRGVONEZTXELXJMASHSOBZLAUYEVIZIZJZPESNTIQTYVNGPRMHYCZWCMCYPXOBTZNWQRQDLUTNBDETJOBEWTEBMYAMYAEGNTNFHIWWRWQDUNMWUAFWOEDCINRXUIVPTODPGGEONSTXWEGEVBBLPFXVREHNNZQYLBRPNHHPUYSUTYOJHGKKQGSYPAUUUUHKSQHSUTZPHBTJSEQGLWSEADAGNQLIQDWVRMPHURXWPAOTIXMZFMSUCDZRJBNAGETGZSLYZHNORVSEFXGICAUUGKFNOIFPHVFZXZFZOANUBNGGUXUWZLVHWXLOLYCQNXODAWOAPTHZKKGSJAGYRYXEEAHDOYDOZUKSYKABDBGYPNLKOUGJWCVBDRNXWTCMUVKKGGABIJWVBEGNNWJHFURDMERBRNYCMZGLLHJRBBYOTQWAEBFQSWZLPEYUZJVGVHJZJMRTKUKAOWHUWBZLKKPEMMDXHCKTXMENLLNCQOEIDFAWRSBVNZDKDFFPRBYKTAOVQEMBVPANILXCHYOEEFQBEYXBWAGEUWHBQLAPIDBAYGXYWVYXWVPUIAJLMFUTWDNEQHYXCVPFADXNIIBQOKRYVTFXMNVGPOUKRXYILSCNLCTHCSENDXOIGWMTDPIUUAVDGSBQNDSVMYLSCTMRCMPBHNXWQIGCLKUFKRACWGDGJKOGRTTGWLCIXIZCFXSQPYQMQMPTDRTIFMTARDUFSRWCOCDUSMMVEESFBBFFRUMGBQYWWMFSIMIIXIDVHQWVDPHFNPUWDTCKUMOGAZNYZOBKRYZJTLTRHHJATNWYKYCEXIUTOFUOZOXUDUEYBMNQTMUZFCXIFZFMFVBVYCXONJJIBHHFSYRGLCKDPRGXGDHMATIATDGTPUPAINPKUHAHOWDCUNUBPQSNXPCJMBJTYPCOIJGCLZLJUAEDREFQBITUYJUFPCKWZNFKZRKHCETYLLBJDIVDAHWXEQQUFFCXYHYGELIPSUACOOKWCVURYTDSXBAKXZOKDHYJPLCUDTEFSCOCYNSGKIYRZENWBHTSRFFCEMSBOULZKYIDIFESVYXDXFGLYHDELFYBRTNXJTVUIVRMUXSCGHBWUKDEXYMMOHZAHQPPMCDOQBBMGYUNKWCIIJQHXYOCFEOHUPHSJKSWREATFCCUOPJNWMKASCSCPVVNLGGWCCFDQCHZKFIXBTEZOWAVXGRWPSCKBBETMEWGIIKCGPBZCERTRRNJZKCPRCJMWQCSSUYTKUZVFZMUBFLEPXXIYVVVOGINRQWKCMZYEFUTVBXUWNCZETLLFPUIWORGRLZFJMVUNEVVLMHEDDGKSYTYLGGRKVKHPADATKKLLTAOVGZPCDPCXDCGDQJMOMLOTIIRXEPRYXCPMNAWYFXUSHOKDPAVCENBNPUYKZJAGVRJZQFUMSFBTIRFSVYWLXSYWDFEAIQINEOWJUGBQBETPGMQZZODIDQOWNHUYURZELEFVSBPLZGFPVMNDUSBGEJOIXLEXBWHNKVAMWMLXDTZWYFZVLNGSEROQXOYZXCVJOWYBXZSKHELNDMXMHIBFUVBBEBIEPSPQFBKQUSGUAUDFCSBYLFYIUXREKIGCYYFBCDBRZECNDZGRDWAIDKSMCULRNIICFJFDJGNXVLMCTKIXQXPVAWFKXHSTFRUXMQLPVMEEKFKGVBXDIIMPDRUXQABVVKNQWENPTUYYCJOZXGFXJEZOYUJCNGHRTBPWPRFRFVQJLHKEHIYZXNOHZPVYSGNYAYFGWGHWCCYCDJZKUWKXQNTRTXFZKNPYTDAZBWQAPCZYGEOCLFGLFUZQMIMZAHYSXTPZIXSMNHDARHYKZAQCGUJVGFBVAIDNDUDEWPXJOLMOAHCLIKHFRGXHYOWOAMRQQMEIBNBYHWLTWAVNJINTXZHZEDHKTKGCIAFPWKWEKVGVKFEUBBGLETIRMBHJQMSUSGDISPGRJUTKGFWXOBPGBKAWCWUAVLIMYHFHMAPLGZRAOIWYZPXDQBVKPJISNNRFVOTANRCWCZGKFSVFKDNQOZAASPGVYTGIPRDEBOICEPVHJRCSPDPDHRTYZNOCUGDAWFSQRAOLYSQIXTGFXBXRVXMJFSNFYHEXWPHUCVMIZLNWDJQLVEFFDERMJVQCYDQKJGFUCQWAWXNUQNHXGVRVCUAQWRUNHEDQSSNXAPDVGRDSGIGYOGAMBQRZYIQGZLEDEYVUAUSACPIHDEDCTDTLDNNPJINTUSFGJJDRUQQZLWAQQSKHVJGMMMOTCXPNCOACRUBIQHCUKEFIPXIRENGDRSCMNGVHSYPIHJZKINCCVZTJTANUTWCDYSRGRENFBPPTSAMODACIIVDWDLEPCCPLJWATIFYBACOWGRWOUTQMOCSSVTWWIRULRYBGRTFFTALWPWVPABLNAGMSCPQGTZFTUWYYIVNOFFXADEHCFWCBSODYRJVQJFFBTASEGNOMJQSMBJMHJNJWUVLKDXYPEDJQMLWTWFIZZOMLBXHVZZFHTBMYRWSHKLKWAMDGBNCXGIIJVEQCDHAQCGWFPEKJCNYNHYRFTYNWQFCAHOZPOUFKYPHXBLRMLGOXVTKPXZDZCSZJCXDARCWOILEGCKECAXCLHIUSSZQLYQIWLJDWNTBESSPRERZFYWJNPOTDNIYPDEEVMCMPFQTRLRQHHDKAQBOSKAVTVBFHPPWSTISSGSZAXISHMSPPAYFMBYVYISQYITBVETPZWLBOQGAYBTTLBDCPHKDMYBTKNDTQXTWUGAUDUCZMWNUVZTSLIZNTWTNUTTXAFWQEBWDZGOSFSAABHFBFJUFLRSPARIBYYCGMDQJKUVHDUUFKITOCZEDWJBXDQXZVIYCFBRAJLULUZHCDEYHCUSECNCXOOFQQACSAIPTEALOFYMGCEOUBHAUCRIUTORHGSGZPOGRQUYHOICISUYZGCELDXWZAGEZIQTFSEVQVNDCHZLZEXLQLTPYBJRTLICGNDNHMOGZEWUVGKISEBAMCLBROJTIJZYZNTWCNOICNVJQVSDFOJUUSXYJVNXSKXGVJBHSVGDBVEHNAHAJHAWELALMILSOOAEKIZGMGRWSLAXNJXVNGLYJXROTKCGSYKYTEVZQMWEODRIBZIYXOPAZSUVIGWVDJIZWVDSYHLMDVFJSDQVNDXRMRUSEDMXAOUISQMGDBRRYCUQRORXNJYDZFLSKKDZDEQFRHBWFWOOQLYCFNETIVSZXPOUKPSJHAONOZDRNZAXUCTJOQNZDCMIXAOEOSDLRJYGJDIFGHROUFRLLDFEUVWNFHVTQRKKTMDLYDWCQWJLTXEZESVSWVAZLRPBNVMZQSLXLKSVZYVXHJBRNHGPTKSKRBMCISUTEFANPSEGMXNADBCHHBAOEVAKCPBMVGNXFAAECTFHJAVBEDXBTOLYFJLYKUOMYQNULMKTHMPPFOZWGUKFSILCIAYQVAYHOWXHGEDVZVIBQCBWHEJSYTDNZTEMAEDCPQIFDYUVCCBMYDMJGMTCLZGZHPWUHBETDKRIZGLXWALAJYDHUWBEIWFBQROYBDURARYHHNRHWGTMYCRUQBXYTIBTEUEJABMZWOTRTCHYXPECVYYXSZYVYPQNJRVZQUZFRBXTSWDNKAWXCRKHAZJJBNXOXLFFCLUEHTEWODGFPUQFWAGYLWLOTPGDTUVNSMQVKDFHXOZBCTIAEMNNYVJFEHZZYGKIRKKTTONQCOIBIRHUTNOBPTYENHOLPHIOVZARNHWSEORDMSIWOVBVPYFONLHBXGALLRZXWXINEMZZEUJGKCCEZLDGWOMDHSPNAZWJQZOMFWXCKFVJPQBNTAOZHCNZRABGHSEAYZYCINTCAAAJGWZGCPMPHFAMAXNYQCZWZCWLMXQFBMCJBYADMXWEUOUCKYOTLRFNQVYKSMDHYLZEEZHRIHRZUEEYAJOTWHZXHMPRXEDUXRPPHPMDMQBQXPEVLROIROKQRMUIFKQSBOGJYEXHVVJZOXMZDFOMNXDFXNVQLTCFBZSXXFMYKBJIRWARAIDUPBQDTONDXWSQYJFKIUWBVXHLNSYHGUPFQUXSOLWINNQWIRAZTPNIYAVEYURVKJFGEQMAHIEOKURMKTUZJQBSEOXWAUEMAQHYBNKUSJIDWBCKTVRJWOCLGCAZQMRDDULHNVFNGTHXRVEQWITQSMRGQIXXKBMFDISJSTMWVWDOSPZTRLLBBVCFQQTBSOPVTTNQZAJIOQBFUHJYBVSVFUQFBOVAFEIBOZOEXGRRJNLKOACELFOVLSEVWDOUSSOQABDVWLWWYWVYUVUXAXNOWQANTHVPVKPTYJJFRKANKBZEAIWZWBUDNTCYWVPKVSNUSVXBYOCERVSKBUVWUQWWBLSUQQBAPMQMEOTYFMSZVXLULKLOVMXTOUIMJPZPGVHSIQJTVCZTZXKQIEJQFUCTCYDXCUBESNPORTEOJFZXBRPQXDOYNCOIURIIWDCTKUSQASKWTZOMQANDJBZOGXXHWAZCYWIFWLGTWSSZXQDPYPSXSCYZRQYOMXCOILKCRQHWZDMTZJTFVKTIDYFZAJXBGGHLIPBJGFJHACPKYJPREOAWUFEQBVXDRHQIODBUNGBNXRSQKBVBRSEIEIWJYSPONGMMVQEBCFTQSLLYLISQMIYZOAJXMYEZXRERTERTTQUHMAVSMYHJEQIOMQUPURFIXBEOUURZUOOSFTXMHYSWDCHJYCRWDCAOQJZJRZAADMWELZPTCVBARAWWGLCVNEKHYPLEIYLKUWDBCZJQSKXHKPENTGTFNFOCRHVGZJZHNQOWOLLBRFJHDZYGRPGZANASIFVKCFSJEXZFPRMREAZTAVOARLLWSLGMZWWKPTCFOMGYMGIAGAPBTYTXFKVQJAAPBWIUASJBAHJNHWVTAXQGILJFTXRVHHJPVGHUZTZMWRRBIWVKRMVCRGITGLNDRIFYXZKZZFLNIHMSPUMZOJKWHIGIUFICOEPGJGUFKLZUKCFCJXWJCGDBSXZPOAWUZVPWTFSWXVSSNJBXGIMIHZINBXCMYRVWPGOJZQNCJFYXDEXZXNJVTWFQUYMSGHKJIUTDGGZXJSTGTIGQTRZIOJYVQUJSITSWNZJIFJUNIVICLIVYUPRXFDCSNCVJRDSPDEHENYUIGJEAJPXGWXRUNLVKWEJDIFDFFQFKXCIJPINAITZAOYWPEMGHVXQSZHIIEHITDXNUGGSRNSDKUAWKCMCZKELGSGUKHLNYOIVFHIWEHRAPAICWOCISZJFTGRGOWGYHUCYFCKAXVLYPITZCDPOUUYQJAITVGAGIZBZSTQNKYXOACVLJLYLYIQYDNFREMCZKYJPEBQFCRDWLICVLASTPKGHMZANJQZCLTUBZHXBLVRTZMZXTCTOZMEDAGFFQCQEBMQRNZLBWAMUNSEDOSKEIZEJGRXUHZZMXATUSWYYSFPLMJPUCGYNBOTDQJYGEQIGACCWVKTEMMJTAJPPYUADNPFJDEXJUIPJNFMMVVWWKTYBMRQCHWDKQDCVLZGNQDLTSKPUIISUITUGVYLAICSTYTACZGEDQBRBCPMDGGOWOCLVKKXMPWYXGJVIUSQSSGXXXKPLUDIUAOWTAZKKXDHIPZZUPRUKKLISDKHVLALASKSQVZYZFMVVFJSZXFSOQCJSZOLIGDCNOVWBIRWRQJEIRBBMEOTUCTTRIVUPZJRIJKIEWQOSRHHCBLQMWGQFSOSECYMOWRDKJNHXXWMJPWLLOGGVVVBPRNCQLIPUHRIKLONOZGSNDBAYRTQZGQFWFPVTZMAYRXOIJKXHEKRWDKDUMHRTZSKDYGIMIZTPHDQSJDFXCKANKZUBUBQZZPZTXDIIDDMKVVRQRVMYGTJLXLQDQNONJWWGOLGHGQHQTRZBVCYJGEFVKRJIYZOCZVCIAQFOAULOOQBDTGHICGFMNDCJGTQJFEEFDBSZOCZTZKYHAEZSYULKROMYLRWOKGNRQSKJGPTJFLZRZSUTVYOOIURSSFMOKANMTFGDZLJLLYZFXUNQAURHOPAJOZECXAMDZNCFFNVEDXGTZHNUJYORTYBXZRILGCSJMJAOFFSFTNNXXJUMXJZCBNPYZKECAKRFHDKZYPDAWR");
    int k = 2666;
    cout << characterReplacement::Solution().characterReplacement(s, k) << endl;
    return 0;
}
//*/
